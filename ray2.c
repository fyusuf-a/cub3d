/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 16:32:11 by fyusuf-a          #+#    #+#             */
/*   Updated: 2020/05/24 20:56:42 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_contact		*next_point_on_horizontal_line(t_game *game, t_player *player,
							t_dda *dda, t_direction *direction)
{
	t_2d current;

	current = dda->x->impact;
	current.x += 0.01 * direction->vector.x;
	if (what_is(game, current) == WALL)
	{
		free(dda->y);
		return (dda->x);
	}
	dda->x->impact.x += direction->vector.x;
	dda->x->impact.y += direction->vector.x * direction->tangent;
	if (dist(player->pos, dda->x->impact) < dist(player->pos, dda->y->impact))
		return (next_point_on_horizontal_line(game, player, dda, direction));
	else
		return (next_point_on_vertical_line(game, player, dda, direction));
}

t_contact		*next_point_on_vertical_line(t_game *game, t_player *player,
					t_dda *dda, t_direction *direction)
{
	t_2d current;

	current = dda->y->impact;
	current.y += 0.01 * direction->vector.y;
	if (what_is(game, current) == WALL)
	{
		free(dda->x);
		return (dda->y);
	}
	dda->y->impact.y += direction->vector.y;
	dda->y->impact.x += direction->vector.y / direction->tangent;
	if (dist(player->pos, dda->x->impact) < dist(player->pos, dda->y->impact))
		return (next_point_on_horizontal_line(game, player, dda, direction));
	else
		return (next_point_on_vertical_line(game, player, dda, direction));
}
