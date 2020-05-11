/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 09:14:47 by fyusuf-a          #+#    #+#             */
/*   Updated: 2020/05/11 15:54:45 by fyusuf-a         ###   ########.fr       */
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

int		key_hook(int key, t_game *game)
{
	t_player	new_player;
	double		step;

	step = 0.02;
	new_player = *game->player;
	if (key == W)
		new_player.pos.y -= step;
	if (key == S)
		new_player.pos.y += step;
	if (key == A)
		new_player.pos.x -= step;
	if (key == D)
		new_player.pos.x += step;
	if (key == LEFT)
		new_player.angle = add_angle(new_player.angle, -step);
	if (key == RIGHT)
		new_player.angle = add_angle(new_player.angle, step);
	if (!t_player_equal(&new_player, game->player)
			&& what_is(game, new_player.pos) == VOID)
	{
		draw(game, 1);
		*game->player = new_player;
		draw(game, 0);
	}
	return (EXIT_SUCCESS);
}

int		main(int argc, char *argv[])
{
	t_game	game;

	g_black.r = 0;
	g_black.g = 0;
	g_black.b = 0;
	g_white.r = 255;
	g_white.g = 255;
	g_white.b = 255;
	g_red.r = 0;
	g_red.g = 255;
	g_red.b = 255;
	if (argc != 2)
		error("Usage: cub3d map.cub");
	initialize_game(argv[1], &game);
	draw(&game, 0);
	mlx_hook(game.conn->win_ptr, KeyPress, KeyPressMask | KeyReleaseMask,
				key_hook, &game);
	/*mlx_key_hook(game.conn->win_ptr, key_hook, &game);*/
	/*mlx_loop_hook(game.conn->win_ptr, loop_hook, &game);*/
	mlx_loop(game.conn->mlx_ptr);
	return (EXIT_SUCCESS);
}
