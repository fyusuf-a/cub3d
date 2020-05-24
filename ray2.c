/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 16:32:11 by fyusuf-a          #+#    #+#             */
/*   Updated: 2020/05/24 23:26:07 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_contact		*next_point_on_vertical_line(t_game *game, t_player *player,
							t_iter *iter, t_direction *direction)
{
	t_2d current;

	current = iter->y->impact;
	current.x += 0.01 * direction->vector.x;
	if (what_is(game, current) == WALL)
	{
		free(iter->x);
		return (iter->y);
	}
	iter->y->impact.x += direction->vector.x;
	iter->y->impact.y += direction->vector.x * direction->tangent;
	if (dist(player->pos, iter->x->impact) < dist(player->pos, iter->y->impact))
		return (next_point_on_horizontal_line(game, player, iter, direction));
	else
		return (next_point_on_vertical_line(game, player, iter, direction));
}

t_contact		*next_point_on_horizontal_line(t_game *game, t_player *player,
					t_iter *iter, t_direction *direction)
{
	t_2d current;

	current = iter->x->impact;
	current.y += 0.01 * direction->vector.y;
	if (what_is(game, current) == WALL)
	{
		free(iter->y);
		return (iter->x);
	}
	iter->x->impact.y += direction->vector.y;
	iter->x->impact.x += direction->vector.y / direction->tangent;
	if (dist(player->pos, iter->x->impact) < dist(player->pos, iter->y->impact))
		return (next_point_on_horizontal_line(game, player, iter, direction));
	else
		return (next_point_on_vertical_line(game, player, iter, direction));
}
