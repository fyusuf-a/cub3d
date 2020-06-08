/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 16:32:11 by fyusuf-a          #+#    #+#             */
/*   Updated: 2020/06/06 18:50:12 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int
	determine_cardinal_point(t_iter *iter)
{
	if (iter->current == HORIZONTAL)
		return (iter->vector.y > 0 ? NORTH : SOUTH);
	else
		return (iter->vector.x > 0 ? WEST : EAST);
}

static t_2d
	what_direction(double angle)
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

void
	initialize_iter(const t_player *player, t_iter *iter)
{
	t_contact	*contact;

	iter->vector = what_direction(player->angle);
	iter->current = HORIZONTAL;
	iter->x.cardinal_point = determine_cardinal_point(iter);
	iter->current = VERTICAL;
	iter->y.cardinal_point = determine_cardinal_point(iter);
	iter->x.impact = what_cell(player->pos);
	iter->y.impact = iter->x.impact;
	iter->x.impact.y += iter->vector.y * 0.5;
	if (iter->vector.x == 0)
		iter->x.impact.x = player->pos.x;
	iter->y.impact.x += iter->vector.x * 0.5;
	if (iter->vector.y == 0)
		iter->y.impact.y = player->pos.y;
	ft_lstclear(&iter->ray, del);
	if (what_is(player->pos) == OBJECT)
	{
		contact = malloc(sizeof(t_contact));
		contact->impact = player->pos;
		add_object_to_list(iter, contact);
	}
}

void
	good_angle_update(const t_player *player, t_iter *iter)
{
	if (iter->current == HORIZONTAL)
	{
		iter->x.impact.y += iter->vector.y;
		iter->x.impact.x += iter->vector.y / iter->tangent;
	}
	else
	{
		iter->y.impact.x += iter->vector.x;
		iter->y.impact.y += iter->vector.x * iter->tangent;
	}
	iter->current = dist(player->pos, iter->x.impact) <
			dist(player->pos, iter->y.impact) ? HORIZONTAL : VERTICAL;
}

void
	bad_angle_update(const t_player *player, t_iter *iter)
{
	(void)player;
	if (iter->current == HORIZONTAL)
		iter->x.impact.y += iter->vector.y;
	else
		iter->y.impact.x += iter->vector.x;
}
