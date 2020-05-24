/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 13:17:38 by fyusuf-a          #+#    #+#             */
/*   Updated: 2020/05/24 23:41:01 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_contact	*next_point_bad_angle(t_game *game, t_player *player,
						t_contact *pos, t_direction *direction)
{
	t_2d current;

	current = pos->impact;
	current.x += 0.01 * direction->vector.x;
	current.y += 0.01 * direction->vector.y;
	if (what_is(game, current) == WALL)
		return (pos);
	pos->impact.x += direction->vector.x;
	pos->impact.y += direction->vector.y;
	return (next_point_bad_angle(game, player, pos, direction));
}

static t_contact	*bad_angle(t_game *game, t_player *player,
								t_iter *iter, t_direction *direction)
{
	if (direction->vector.y == 0)
	{
		free(iter->x);
		return (next_point_bad_angle(game, player, iter->y, direction));
	}
	if (direction->vector.x == 0)
	{
		free(iter->y);
		return (next_point_bad_angle(game, player, iter->x, direction));
	}
	return (NULL);
}

t_2d				what_direction(double angle)
{
	t_2d	direction;

	angle = principal_measure(angle);
	if (angle > 0 && angle < M_PI)
		direction.y = 1;
	else if (angle == 0 || angle == M_PI)
		direction.y = 0;
	else
		direction.y = -1;
	if (angle > -M_PI / 2 && angle < M_PI / 2)
		direction.x = 1;
	else if (angle == M_PI / 2 || angle == -M_PI / 2)
		direction.x = 0;
	else
		direction.x = -1;
	return (direction);
}

static void			initialize_pos(t_player *player, t_iter *iter,
											t_direction *direction)
{
	iter->x->impact = what_cell(player->pos);
	iter->x->impact.y += direction->vector.y * 0.5;
	iter->x->cardinal_point = direction->vector.y > 0 ? SOUTH : NORTH;
	if (direction->vector.x == 0)
		iter->x->impact.x = player->pos.x;
	iter->y->impact = what_cell(player->pos);
	iter->y->impact.x += direction->vector.x * 0.5;
	iter->y->cardinal_point = direction->vector.x > 0 ? EAST : WEST;
	if (direction->vector.y == 0)
		iter->y->impact.y = player->pos.y;
}
t_contact			contact_with_wall(t_game *game, t_player *player)
{
	t_direction	direction;
	t_iter		iter;
	t_contact	*contact;

	iter.x = malloc(sizeof(t_contact));
	iter.y = malloc(sizeof(t_contact));
	direction.vector = what_direction(player->angle);
	initialize_pos(player, &iter, &direction);
	if ((contact = bad_angle(game, player, &iter, &direction)))
		return (*contact);
	direction.tangent = tan(player->angle);
	iter.y->impact.y = direction.tangent * (iter.y->impact.x - player->pos.x)
					+ player->pos.y;
	iter.x->impact.x = (iter.x->impact.y - player->pos.y) / direction.tangent
					+ player->pos.x;
	if (dist(player->pos, iter.x->impact) < dist(player->pos, iter.y->impact))
		return (*next_point_on_horizontal_line(game, player, &iter,
														&direction));
	else
		return (*next_point_on_vertical_line(game, player, &iter, &direction));
}
