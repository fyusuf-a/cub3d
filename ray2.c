/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 16:32:11 by fyusuf-a          #+#    #+#             */
/*   Updated: 2020/05/18 17:09:16 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_2d		next_point_on_horizontal_line(t_game *game, t_player *player, t_2d xpos, t_2d ypos,
											t_direction *direction)
{
	t_2d current;

	current = xpos;
	current.x += 0.01 * direction->vector.x;
	if (what_is(game, current) == WALL)
		return (xpos);
	xpos.x += direction->vector.x;
	xpos.y += direction->vector.x * direction->tangent;
	if (dist(player->pos, xpos) < dist(player->pos, ypos))
		return (next_point_on_horizontal_line(game, player, xpos, ypos, direction));
	else
		return (next_point_on_vertical_line(game, player, xpos, ypos, direction));
}

t_2d		next_point_on_vertical_line(t_game *game, t_player *player, t_2d xpos, t_2d ypos,
											t_direction *direction)
{
	t_2d current;

	current = ypos;
	current.y += 0.01 * direction->vector.y;
	if (what_is(game, current) == WALL)
		return (ypos);
	ypos.y += direction->vector.y;
	ypos.x += direction->vector.y / direction->tangent;
	if (dist(player->pos, xpos) < dist(player->pos, ypos))
		return (next_point_on_horizontal_line(game, player, xpos, ypos, direction));
	else
		return (next_point_on_vertical_line(game, player, xpos, ypos, direction));
}
