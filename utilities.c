/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 17:31:50 by fyusuf-a          #+#    #+#             */
/*   Updated: 2020/06/15 17:16:19 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_object	what_is(t_2d pos)
{
	t_2d_int	cell;

	if (pos.x >= -0.5 && pos.y >= -0.5 &&
			pos.x <= g_game.map->dim.x + 0.5 && pos.y <= g_game.map->dim.y)
	{
		cell.x = pos.x + 0.5;
		cell.y = pos.y + 0.5;
		return (g_game.map->grid[cell.y][cell.x]);
	}
	return (UNDEFINED);
}

t_2d		what_cell(t_2d pos)
{
	pos.x = (int)(pos.x + 0.5);
	pos.y = (int)(pos.y + 0.5);
	return (pos);
}

double		dist(t_2d point1, t_2d point2)
{
	return (sqrt(pow(point1.x - point2.x, 2) + pow(point1.y - point2.y, 2)));
}

int			t_player_equal(t_player *player1, t_player *player2)
{
	if (player1->pos.x == player2->pos.x && player1->pos.y == player2->pos.y
			&& principal_measure(player1->angle) ==
											principal_measure(player2->angle))
		return (1);
	return (0);
}

double		principal_measure(double angle)
{
	while (angle <= -M_PI)
		angle += 2 * M_PI;
	while (angle > M_PI)
		angle -= 2 * M_PI;
	return (angle);
}
