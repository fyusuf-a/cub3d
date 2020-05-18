/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 15:29:13 by fyusuf-a          #+#    #+#             */
/*   Updated: 2020/05/18 17:12:50 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double		map_dim_to_pixel(t_game *game, t_image *image, int axis, double x)
{
	if (axis == YAXIS)
		return (x / game->map->dim.y * image->res.y);
	return (x / game->map->dim.x * image->res.x);
}

t_2d_int	map_size_to_pixel(t_game *game, t_image *image, t_2d size)
{
	t_2d_int	ret;

	ret.x = map_dim_to_pixel(game, image, XAXIS, size.x);
	ret.y = map_dim_to_pixel(game, image, YAXIS, size.y);
	return (ret);
}

t_2d_int	map_pos_to_pixel(t_game *game, t_image *image, t_2d pos)
{
	pos.x = pos.x + 0.5;
	pos.y = pos.y + 0.5;
	return (map_size_to_pixel(game, image, pos));
}

void		draw_fov(t_game *game, t_player *player, t_color color)
{
	t_2d			dim;
	t_2d			contact;
	t_line_params	params;

	params.color = color;
	params.thickness = map_dim_to_pixel(game, game->img_map, 0, 0.01);
	dim.x = 0.05;
	dim.y = 0.05;
	contact = contact_with_wall(game, player);
	draw_line(game->img_map, &params,
		map_pos_to_pixel(game, game->img_map, player->pos),
		map_pos_to_pixel(game, game->img_map, contact));
	draw_rectangle_from_center(game->img_map, color,
			map_pos_to_pixel(game, game->img_map, contact),
			map_size_to_pixel(game, game->img_map, dim));
}

void		draw_minimap(t_game *game, t_player *old_player, t_player *new_player)
{
	game->img_map->buffered = 1;
	draw_player(game, old_player, g_black);
	draw_fov(game, old_player, g_black);
	draw_walls_and_contours(game);
	draw_player(game, new_player, g_white);
	draw_fov(game, new_player, g_white);
	copy_from_buffer(game->img_map);
	mlx_put_image_to_window(game->conn->mlx_ptr, game->conn->win_ptr,
			game->img_map->ptr, 0, 0);
}
