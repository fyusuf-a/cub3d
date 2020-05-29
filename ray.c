/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 13:17:38 by fyusuf-a          #+#    #+#             */
/*   Updated: 2020/05/29 17:53:03 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	next_point_bad_angle(t_player *player, t_iter *iter)
{
	t_2d		displaced;
	t_object	current_object;

	displaced = iter->current == HORIZONTAL ? iter->x : iter->y;
	displaced.x += 0.01 * iter->vector.x;
	displaced.y += 0.01 * iter->vector.y;
	current_object = what_is(displaced);
	if (current_object == WALL || current_object == OBJECT)
	{
		add_object_to_list(iter);
		if (current_object == WALL)
		{
			determine_cardinal_point(iter);
			return ;
		}
	}
	if (iter->current == HORIZONTAL)
		iter->x.y += iter->vector.y;
	else
		iter->y.x += iter->vector.x;
	next_point_bad_angle(player, iter);
}

t_2d		what_direction(double angle)
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

static void	initialize_iter(t_player *player, t_iter *iter)
{
	iter->ray = malloc(sizeof(t_ray));
	iter->ray->list = NULL;
	iter->x = what_cell(player->pos);
	iter->x.y += iter->vector.y * 0.5;
	if (iter->vector.x == 0)
		iter->x.x = player->pos.x;
	iter->y = what_cell(player->pos);
	iter->y.x += iter->vector.x * 0.5;
	if (iter->vector.y == 0)
		iter->y.y = player->pos.y;
}

t_ray		*contact_with_wall(t_player *player)
{
	t_iter		iter;

	iter.vector = what_direction(player->angle);
	initialize_iter(player, &iter);
	if (iter.vector.y == 0 || iter.vector.x == 0)
	{
		iter.current = iter.vector.y == 0 ? VERTICAL : HORIZONTAL;
		next_point_bad_angle(player, &iter);
	}
	else
	{
		iter.tangent = tan(player->angle);
		iter.y.y = iter.tangent * (iter.y.x - player->pos.x)
						+ player->pos.y;
		iter.x.x = (iter.x.y - player->pos.y) / iter.tangent
						+ player->pos.x;
		iter.current = dist(player->pos, iter.x) < dist(player->pos, iter.y) ?
							HORIZONTAL : VERTICAL;
		next_point_good_angle(player, &iter);
	}
	return (iter.ray);
}
