/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 16:32:11 by fyusuf-a          #+#    #+#             */
/*   Updated: 2020/06/06 17:39:33 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				determine_cardinal_point(t_iter *iter)
{
	if (iter->current == HORIZONTAL)
		return (iter->vector.y > 0 ? NORTH : SOUTH);
	else
		return (iter->vector.x > 0 ? WEST : EAST);
}

void			add_object_to_list(t_iter *iter, t_contact *contact)
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

static void		update(const t_player *player, t_iter *iter)
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

void			next_point_good_angle(const t_player *player, t_iter *iter)
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
	update(player, iter);
	next_point_good_angle(player, iter);
}
