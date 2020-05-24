/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 13:17:38 by fyusuf-a          #+#    #+#             */
/*   Updated: 2020/05/24 21:07:36 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_contact	*next_point_bad_angle(t_game *game, t_player *player,
						t_contact *pos, t_direction *direction)
{
	t_2d pos_cpy;

	pos_cpy = pos->impact;
	pos_cpy.x += 0.01 * direction->vector.x;
	pos_cpy.y += 0.01 * direction->vector.y;
	if (what_is(game, pos_cpy) == WALL)
		return (pos);
	pos->impact.x += direction->vector.x;
	pos->impact.y += direction->vector.y;
	return (next_point_bad_angle(game, player, pos, direction));
}

static t_contact	*bad_angle(t_game *game, t_player *player,
								t_dda *dda, t_direction *direction)
{
	if (direction->vector.y == 0)
	{
		free(dda->y);
		return (next_point_bad_angle(game, player, dda->x, direction));
	}
	if (direction->vector.x == 0)
	{
		free(dda->x);
		return (next_point_bad_angle(game, player, dda->y, direction));
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

static void			initialize_pos(t_player *player, t_contact *next_x,
							t_contact *next_y, t_direction *direction)
{
	next_x->impact = what_cell(player->pos);
	next_x->impact.x += direction->vector.x * 0.5;
	next_x->cardinal_point = direction->vector.y > 0 ? SOUTH : NORTH;
	if (direction->vector.y == 0)
		next_x->impact.y = player->pos.y;
	next_y->impact = what_cell(player->pos);
	next_y->impact.y += direction->vector.y * 0.5;
	next_y->cardinal_point = direction->vector.x > 0 ? WEST : EAST;
	if (direction->vector.x == 0)
		next_y->impact.x = player->pos.x;
}

t_contact			contact_with_wall(t_game *game, t_player *player)
{
	t_direction	direction;
	t_dda		dda;
	t_contact	*contact;

	dda.x = malloc(sizeof(t_contact));
	dda.y = malloc(sizeof(t_contact));
	direction.vector = what_direction(player->angle);
	initialize_pos(player, dda.x, dda.y, &direction);
	if ((contact = bad_angle(game, player, &dda, &direction)))
		return (*contact);
	direction.tangent = tan(player->angle);
	dda.x->impact.y = direction.tangent * (dda.x->impact.x - player->pos.x)
					+ player->pos.y;
	dda.y->impact.x = (dda.y->impact.y - player->pos.y) / direction.tangent
					+ player->pos.x;
	if (dist(player->pos, dda.x->impact) < dist(player->pos, dda.y->impact))
		return (*next_point_on_horizontal_line(game, player, &dda, &direction));
	else
		return (*next_point_on_vertical_line(game, player, &dda, &direction));
}
