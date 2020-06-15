/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 09:14:47 by fyusuf-a          #+#    #+#             */
/*   Updated: 2020/06/15 17:54:36 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void
	update_pos(int key, double step, t_player *new_player, t_player *player)
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
		new_player->angle -= step;
	if (key == RIGHT)
		new_player->angle += step;
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
	key_hook(int key, t_game *game)
{
	t_player	new_player;
	double		step;
	t_object	current_object;
	int			draw_bool;
	t_2d		player_cell;

	step = 0.1;
	new_player = *game->player;
	update_pos(key, step, &new_player, game->player);
	current_object = what_is(new_player.pos);
	draw_bool = !t_player_equal(&new_player, game->player)
		&& (current_object == VOID || current_object == OBJECT)
		&& far_from_wall(new_player.pos);
	if (current_object == OBJECT)
	{
		player_cell = what_cell(new_player.pos);
		draw_bool = draw_bool &&
			dist(new_player.pos, player_cell) >= 0.5 + SCREEN_DISTANCE;
	}
	if (draw_bool)
	{
		draw(game->player, &new_player);
		*game->player = new_player;
	}
	return (EXIT_SUCCESS);
}

int
	main(int argc, char *argv[])
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
	if (argc != 2)
		error("Usage: cub3d map.cub");
	initialize_game(argv[1]);
	draw(g_game.player, g_game.player);
	mlx_hook(g_game.conn->win_ptr, KeyPress, KeyPressMask | KeyReleaseMask,
				key_hook, &g_game);
	/*mlx_key_hook(game.conn->win_ptr, key_hook, &g_game);*/
	/*mlx_loop_hook(game.conn->win_ptr, loop_hook, &g_game);*/
	mlx_loop(g_game.conn->mlx_ptr);
	free_game();
	return (EXIT_SUCCESS);
}
