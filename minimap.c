/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 15:29:13 by fyusuf-a          #+#    #+#             */
/*   Updated: 2020/05/11 16:15:32 by fyusuf-a         ###   ########.fr       */
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

void		draw_fov(t_game *game, int destroy)
{
	t_2d			dim;
	t_color			color;
	t_2d			contact;
	t_line_params	params;

	if (destroy)
		params.color = g_black;
	else
		params.color = g_red;
	params.thickness = map_dim_to_pixel(game, game->img_map, 0, 0.01);
	dim.x = 0.05;
	dim.y = 0.05;
	contact = contact_with_wall(game, game->player->angle);
	draw_line(game->img_map, &params,
		map_pos_to_pixel(game, game->img_map, game->player->pos),
		map_pos_to_pixel(game, game->img_map, contact));
	draw_rectangle_from_center(game->img_map, color,
			map_pos_to_pixel(game, game->img_map, contact),
			map_size_to_pixel(game, game->img_map, dim));
}

void		draw_minimap(t_game *game, int destroy)
{
	draw_player(game, destroy);
	draw_fov(game, destroy);
	draw_walls_and_contours(game);
	mlx_put_image_to_window(game->conn->mlx_ptr, game->conn->win_ptr,
			game->img_map->ptr, 0, 0);
}
