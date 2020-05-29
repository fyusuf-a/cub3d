/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 09:14:47 by fyusuf-a          #+#    #+#             */
/*   Updated: 2020/05/29 15:12:28 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	add_angle(double angle, double diff)
{
	double ret;

	ret = angle + diff;
	while (ret <= -M_PI)
		ret += 2 * M_PI;
	while (ret > M_PI)
		ret -= 2 * M_PI;
	return (ret);
}

void	update_pos(int key, double step, t_player *new_player, t_player *player)
{
	if (key == W)
	{
		new_player->pos.x += step * cos(player->angle);
		new_player->pos.y += step * sin(player->angle);
	}
	if (key == S)
	{
		new_player->pos.x -= step * cos(player->angle);
		new_player->pos.y -= step * sin(player->angle);
	}
	if (key == A)
	{
		new_player->pos.x += step * sin(player->angle);
		new_player->pos.y -= step * cos(player->angle);
	}
	if (key == D)
	{
		new_player->pos.x -= step * sin(player->angle);
		new_player->pos.y += step * cos(player->angle);
	}
	if (key == LEFT)
		new_player->angle = principal_measure(new_player->angle - step);
	if (key == RIGHT)
		new_player->angle = principal_measure(new_player->angle + step);
}

int		key_hook(int key, t_game *game)
{
	t_player	new_player;
	double		step;

	step = 0.02;
	new_player = *game->player;
	update_pos(key, step, &new_player, game->player);
	if (!t_player_equal(&new_player, game->player)
			&& what_is(new_player.pos) == VOID)
	{
		draw(game->player, &new_player);
		*game->player = new_player;
	}
	return (EXIT_SUCCESS);
}

int		main(int argc, char *argv[])
{
	g_black.r = 0;
	g_black.g = 0;
	g_black.b = 0;
	g_white.r = 255;
	g_white.g = 255;
	g_white.b = 255;
	g_red.r = 255;
	g_red.g = 0;
	g_red.b = 0;
	g_blue.r = 0;
	g_blue.g = 0;
	g_blue.b = 255;
	g_green.r = 0;
	g_green.g = 255;
	g_green.b = 0;
	if (argc != 2)
		error("Usage: cub3d map.cub");
	initialize_game(argv[1]);
	draw(g_game.player, g_game.player);
	mlx_hook(g_game.conn->win_ptr, KeyPress, KeyPressMask | KeyReleaseMask,
				key_hook, &g_game);
	/*mlx_key_hook(game.conn->win_ptr, key_hook, &g_game);*/
	/*mlx_loop_hook(game.conn->win_ptr, loop_hook, &g_game);*/
	mlx_loop(g_game.conn->mlx_ptr);
	return (EXIT_SUCCESS);
}
