/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 15:28:47 by fyusuf-a          #+#    #+#             */
/*   Updated: 2020/06/20 11:24:19 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		initialize_color(t_color *color)
{
	color->r = -1;
	color->g = -1;
	color->b = -1;
}

static t_image	*initialize_minimap(void)
{
	t_2d_int	res;
	t_image		*ret;

	if (g_game.map.dim.x < g_game.map.dim.y)
	{
		res.y = g_game.config.resolution.y;
		res.x = res.y / g_game.map.dim.y * g_game.map.dim.x;
	}
	else
	{
		res.x = g_game.config.resolution.x;
		res.y = res.x / g_game.map.dim.x * g_game.map.dim.y;
	}
	res.x /= 3;
	res.y /= 3;
	ret = initialize_image(res, 255);
	/*ret->buffered = 1;*/
	return (ret);
}

void			initialize_game(const char *file)
{
	g_game.player.pos.x = -1;
	g_game.player.pos.y = -1;
	initialize_color(&(g_game.config.floor));
	initialize_color(&(g_game.config.ceiling));
	if (!(g_game.conn.mlx_ptr = mlx_init()))
		error("initialize_game : mlx_init failed");
	parse(file);
	if (!(g_game.conn.win_ptr = mlx_new_window(g_game.conn.mlx_ptr,
			g_game.config.resolution.x, g_game.config.resolution.y, "cub3d")))
		error("initialize_game: mlx_new_window failed");
	g_game.img_view = initialize_image(g_game.config.resolution, 0);
	/*g_game.img_view->buffered = 1;*/
	g_game.img_map = initialize_minimap();
	g_game.screen_height = 2 * SCREEN_DISTANCE *
		(double)g_game.img_view->res.y / (double)g_game.img_view->res.x;
}
