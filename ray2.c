/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 16:32:11 by fyusuf-a          #+#    #+#             */
/*   Updated: 2020/05/29 17:58:15 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			determine_cardinal_point(t_iter *iter)
{
	if (iter->current == HORIZONTAL)
		iter->ray->cardinal_point = iter->vector.y > 0 ? SOUTH : NORTH;
	else
		iter->ray->cardinal_point = iter->vector.x > 0 ? EAST : WEST;
}

void			add_object_to_list(t_iter *iter)
{
	t_2d		*new_link;

	new_link = malloc(sizeof(t_2d));
	*new_link = iter->current == HORIZONTAL ? iter->x : iter->y;
	if (!iter->ray->list && !(iter->ray->list = ft_lstnew(new_link)))
		error("add_object_to_list: could not create list");
	else
	{
		if (ft_lstadd_elem(&iter->ray->list, new_link))
			error("add_object_to_list: could not add object to list");
	}
}

static void		update(t_player *player, t_iter *iter)
{
	if (iter->current == HORIZONTAL)
	{
		iter->x.y += 0.99 * iter->vector.y;
		iter->x.x += iter->vector.y / iter->tangent;
	}
	else
	{
		iter->y.x += 0.99 * iter->vector.x;
		iter->y.y += iter->vector.x * iter->tangent;
	}
	iter->current = (dist(player->pos, iter->x) < dist(player->pos, iter->y)) ?
						HORIZONTAL : VERTICAL;
}

void			next_point_good_angle(t_player *player, t_iter *iter)
{
	t_object	current_object;

	if (iter->current == HORIZONTAL)
	{
		iter->x.y += 0.01 * iter->vector.y;
		current_object = what_is(iter->x);
	}
	else
	{
		iter->y.x += 0.01 * iter->vector.x;
		current_object = what_is(iter->y);
	}
	if (current_object == WALL || current_object == OBJECT)
	{
		add_object_to_list(iter);
		if (current_object == WALL)
		{
			determine_cardinal_point(iter);
			return ;
		}
	}
	update(player, iter);
	next_point_good_angle(player, iter);
}
