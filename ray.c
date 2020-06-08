/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 13:17:38 by fyusuf-a          #+#    #+#             */
/*   Updated: 2020/06/06 18:47:35 by fyusuf-a         ###   ########.fr       */
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

void		add_object_to_list(t_iter *iter, t_contact *contact)
{
	t_contact	*cpy;

	cpy = malloc(sizeof(t_contact));
	*cpy = *contact;
	if (!iter->ray)
	{
		if (!(iter->ray = ft_lstnew(cpy)))
			error("add_object_to_list: could not create list");
		return ;
	}
	if (ft_lstadd_elem(&iter->ray, cpy))
		error("add_object_to_list: could not add object to list");
}

static void	next_point(const t_player *player, t_iter *iter)
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
	iter->next_point_update(player, iter);
	next_point(player, iter);
}

t_list		*contact_with_wall(const t_player *player, t_iter *iter)
{
	initialize_iter(player, iter);
	if (iter->vector.y == 0 || iter->vector.x == 0)
	{
		iter->current = iter->vector.y == 0 ? VERTICAL : HORIZONTAL;
		iter->x.cardinal_point = determine_cardinal_point(iter);
		iter->y.cardinal_point = determine_cardinal_point(iter);
		iter->next_point_update = &bad_angle_update;
		next_point(player, iter);
		return (iter->ray);
	}
	iter->tangent = tan(player->angle);
	iter->y.impact.y = iter->tangent * (iter->y.impact.x - player->pos.x)
					+ player->pos.y;
	iter->x.impact.x = (iter->x.impact.y - player->pos.y) / iter->tangent
					+ player->pos.x;
	iter->current = dist(player->pos, iter->x.impact) <
		dist(player->pos, iter->y.impact) ? HORIZONTAL : VERTICAL;
	iter->next_point_update = &good_angle_update;
	next_point(player, iter);
	return (iter->ray);
}
