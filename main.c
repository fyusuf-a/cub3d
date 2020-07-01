/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 09:14:47 by fyusuf-a          #+#    #+#             */
/*   Updated: 2020/07/01 11:11:50 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void
	update_pos(t_player *new_player, t_player *player)
{
	if (g_game.keyboard.w)
	{
		new_player->pos.x += STEP * cos(player->angle);
		new_player->pos.y += STEP * sin(player->angle);
	}
	if (g_game.keyboard.s)
	{
		new_player->pos.x -= STEP * cos(player->angle);
		new_player->pos.y -= STEP * sin(player->angle);
	}
	if (g_game.keyboard.a)
	{
		new_player->pos.x += STEP * sin(player->angle);
		new_player->pos.y -= STEP * cos(player->angle);
	}
	if (g_game.keyboard.d)
	{
		new_player->pos.x -= STEP * sin(player->angle);
		new_player->pos.y += STEP * cos(player->angle);
	}
	if (g_game.keyboard.left)
		new_player->angle -= STEP;
	if (g_game.keyboard.right)
		new_player->angle += STEP;
}

static int
	far_from_wall(t_2d pos)
{
	t_2d new_pos;

	new_pos = pos;
	new_pos.x += SCREEN_DISTANCE;
	if (what_is(new_pos) == WALL)
		return (0);
	new_pos = pos;
	new_pos.x -= SCREEN_DISTANCE;
	if (what_is(new_pos) == WALL)
		return (0);
	new_pos = pos;
	new_pos.y += SCREEN_DISTANCE;
	if (what_is(new_pos) == WALL)
		return (0);
	new_pos = pos;
	new_pos.y -= SCREEN_DISTANCE;
	if (what_is(new_pos) == WALL)
		return (0);
	return (1);
}

int
	main_loop(t_game *game)
{
	t_player	new_player;
	t_object	current_object;
	int			draw_bool;
	t_2d		player_cell;

	new_player = game->player;
	update_pos(&new_player, &game->player);
	current_object = what_is(new_player.pos);
	draw_bool = !t_player_equal(&new_player, &game->player);
	draw_bool = draw_bool && far_from_wall(new_player.pos);
	if (current_object == OBJECT)
	{
		player_cell = what_cell(new_player.pos);
		draw_bool = draw_bool &&
			dist(new_player.pos, player_cell) >= 0.5 + SCREEN_DISTANCE;
	}
	if (draw_bool)
	{
		draw(&game->player, &new_player);
		game->player = new_player;
	}
	mlx_do_sync(g_game.conn.mlx_ptr);
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
	/*printf("%d %ld\n", DestroyNotify, StructureNotifyMask);*/
	/*mlx_hook(g_game.conn.win_ptr, 33, 1L << 17,*/
	mlx_hook(g_game.conn.win_ptr, DestroyNotify, StructureNotifyMask,
				free_and_exit_game, &g_game);
	mlx_loop_hook(g_game.conn.mlx_ptr, main_loop, &g_game);
	mlx_loop(g_game.conn.mlx_ptr);
}
