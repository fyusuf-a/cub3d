/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 13:17:38 by fyusuf-a          #+#    #+#             */
/*   Updated: 2020/05/18 17:08:45 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_2d	next_point_bad_angle(t_game *game, t_player *player, t_2d pos,
		t_direction *direction)
{
	t_2d pos_cpy;

	pos_cpy = pos;
	pos_cpy.x += 0.01 * direction->vector.x;
	pos_cpy.y += 0.01 * direction->vector.y;
	if (what_is(game, pos_cpy) == WALL)
		return (pos);
	pos.x += direction->vector.x;
	pos.y += direction->vector.y;
	return (next_point_bad_angle(game, player, pos, direction));
}

t_2d		what_direction(double angle)
{
	t_2d	direction;

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

static void	initialize_pos(t_player *player, t_2d *next_x, t_2d *next_y,
				t_direction *direction)
{
	*next_x = what_cell(player->pos);
	next_x->x += direction->vector.x * 0.5;
	if (direction->vector.y == 0)
		next_x->y = player->pos.y;
	*next_y = what_cell(player->pos);
	next_y->y += direction->vector.y * 0.5;
	if (direction->vector.x == 0)
		next_y->x = player->pos.x;
}

t_2d		contact_with_wall(t_game *game, t_player *player)
{
	t_direction	direction;
	t_2d		next_x;
	t_2d		next_y;

	direction.vector = what_direction(player->angle);
	initialize_pos(player, &next_x, &next_y, &direction);
	if (direction.vector.y == 0)
		return (next_point_bad_angle(game, player, next_x, &direction));
	if (direction.vector.x == 0)
		return (next_point_bad_angle(game, player, next_y, &direction));
	direction.tangent = tan(player->angle);
	next_x.y = direction.tangent * (next_x.x - player->pos.x)
					+ player->pos.y;
	next_y.x = (next_y.y - player->pos.y) / direction.tangent
					+ player->pos.x;
	if (dist(game->player->pos, next_x) < dist(player->pos, next_y))
		return (next_point_on_horizontal_line(game, player, next_x, next_y,
					&direction));
	else
		return (next_point_on_vertical_line(game, player, next_x, next_y,
					&direction));
}
