/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 15:28:47 by fyusuf-a          #+#    #+#             */
/*   Updated: 2020/06/29 22:33:30 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			initialize_config(void)
{
	g_game.config.floor = -1;
	g_game.config.ceiling = -1;
}

void			initialize_game(const char *file)
{
	g_game.map.grid = NULL;
	g_game.player.pos.x = -1;
	g_game.player.pos.y = -1;
	initialize_config();
	if (!(g_game.conn.mlx_ptr = mlx_init()))
		error("initialize_game : mlx_init failed");
	parse(file);
	if (!(g_game.conn.win_ptr = mlx_new_window(g_game.conn.mlx_ptr,
			g_game.config.resolution.x, g_game.config.resolution.y, "cub3d")))
		error("initialize_game: mlx_new_window failed");
	g_game.img_view = initialize_image(g_game.config.resolution);
	g_game.img_map = initialize_minimap();
	g_game.screen_height = 2 * SCREEN_DISTANCE *
		(double)g_game.img_view->res.y / (double)g_game.img_view->res.x;
}
