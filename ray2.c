/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 16:32:11 by fyusuf-a          #+#    #+#             */
/*   Updated: 2020/05/29 13:43:39 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		del(void *content)
{
	(void)content;
}

void			free_ray(t_ray *ray)
{
	ft_lstclear(&ray->list, del);
	free(ray);
}

void			add_object_to_list(t_iter *iter)
{
	t_2d		*new_link;

	new_link = malloc(sizeof(t_2d));
	*new_link = iter->current == HORIZONTAL ? iter->x : iter->y;
	if (!iter->ray->list && !ft_lstnew(new_link))
		error("add_object_to_list: could not create list");
	else
	{
		if (ft_lstadd_elem(&iter->ray->list, new_link))
			error("add_object_to_list: could not add object to list");
	}
}

t_iter		*next_point_good_angle(t_game *game, t_player *player,
							t_iter *iter)
{
	t_2d		displaced;
	t_object	current_object;

	displaced = iter->current == HORIZONTAL ? iter->x : iter->y;
	displaced.x += 0.01 * iter->vector.x;
	current_object = what_is(game, displaced);
	if (what_is(game, displaced) == WALL || current_object == OBJECT)
	{
		add_object_to_list(iter);
		if (current_object == WALL)
			return (iter);
	}
	if (iter->current == HORIZONTAL)
	{
		iter->x.y += iter->vector.y;
		iter->x.x += iter->vector.y / iter->tangent;
	}
	else
	{
		iter->y.x += iter->vector.x;
		iter->y.y += iter->vector.x * iter->tangent;
	}
	iter->current = dist(player->pos, iter->x) < dist(player->pos, iter->y) ?
						HORIZONTAL : VERTICAL;
	return (next_point_good_angle(game, player, iter));
}
