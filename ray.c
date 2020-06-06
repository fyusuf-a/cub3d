/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 13:17:38 by fyusuf-a          #+#    #+#             */
/*   Updated: 2020/06/06 18:09:04 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_2d		displaced(t_contact *contact)
{
	t_2d	ret;

	ret = contact->impact;
	if (contact->cardinal_point == NORTH)
		ret.y += 0.01;
	else if (contact->cardinal_point == SOUTH)
		ret.y -= 0.01;
	else if (contact->cardinal_point == EAST)
		ret.x -= 0.01;
	else
		ret.x += 0.01;
	return (ret);
}

static void	next_point_bad_angle(const t_player *player, t_iter *iter)
{
	t_object	current_object;
	t_contact	*contact;

	contact = iter->current == HORIZONTAL ? &iter->x : &iter->y;
	current_object = what_is(displaced(contact));
	if (current_object == WALL || current_object == OBJECT)
	{
		add_object_to_list(iter, contact);
		if (current_object == WALL)
			return ;
	}
	if (iter->current == HORIZONTAL)
		iter->x.impact.y += iter->vector.y;
	else
		iter->y.impact.x += iter->vector.x;
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

	/*if (what_is(player->pos) == OBJECT)*/
	/*{*/
		/*contact = malloc(sizeof(t_contact));*/
		/*contact->cardinal_point = iter->x;*/
		/*add_object_to_list(iter, contact);*/


	/*}*/

static void	initialize_iter(const t_player *player, t_iter *iter)
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

t_list		*contact_with_wall(const t_player *player, t_iter *iter)
{
	initialize_iter(player, iter);
	if (iter->vector.y == 0 || iter->vector.x == 0)
	{
		iter->current = iter->vector.y == 0 ? VERTICAL : HORIZONTAL;
		iter->x.cardinal_point = determine_cardinal_point(iter);
		iter->y.cardinal_point = determine_cardinal_point(iter);
		next_point_bad_angle(player, iter);
		return (iter->ray);
	}
	iter->tangent = tan(player->angle);
	iter->y.impact.y = iter->tangent * (iter->y.impact.x - player->pos.x)
					+ player->pos.y;
	iter->x.impact.x = (iter->x.impact.y - player->pos.y) / iter->tangent
					+ player->pos.x;
	iter->current = dist(player->pos, iter->x.impact) <
		dist(player->pos, iter->y.impact) ? HORIZONTAL : VERTICAL;
	next_point_good_angle(player, iter);
	return (iter->ray);
}
