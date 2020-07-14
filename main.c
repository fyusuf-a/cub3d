/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 09:14:47 by fyusuf-a          #+#    #+#             */
/*   Updated: 2020/07/14 11:51:02 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int
	main_loop(t_game *game)
{
	t_player	new_player;

	new_player = update_pos(g_game.player);
	update_angle(&new_player);
	if (!t_player_equal(&g_game.player, &new_player))
	{
		draw(&game->player, &new_player);
		game->player = new_player;
		mlx_do_sync(g_game.conn.mlx_ptr);
	}
	return (EXIT_SUCCESS);
}

int
	main(int argc, char *argv[])
{
	if (argc != 2)
	{
		ft_dprintf(2, "Error\nUsage: cub3d map.cub");
		exit(EXIT_FAILURE);
	}
	initialize_game(argv[1]);
	draw(&g_game.player, &g_game.player);
	/*print_bmp(g_game.img_view, "./screenshot.bmp");*/
	mlx_do_key_autorepeaton(g_game.conn.mlx_ptr);
	mlx_hook(g_game.conn.win_ptr, KeyPress, KeyPressMask,
				key_pressed, &g_game);
	mlx_hook(g_game.conn.win_ptr, KeyRelease, KeyReleaseMask,
				key_released, &g_game);
	mlx_hook(g_game.conn.win_ptr, DestroyNotify, StructureNotifyMask,
				free_and_exit_game, &g_game);
	mlx_loop_hook(g_game.conn.mlx_ptr, main_loop, &g_game);
	mlx_loop(g_game.conn.mlx_ptr);
}
