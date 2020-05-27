/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 15:29:13 by fyusuf-a          #+#    #+#             */
/*   Updated: 2020/05/27 14:37:48 by fyusuf-a         ###   ########.fr       */
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
	t_contact		contact;
	t_line_params	params;
	t_2d_int		impact_img;
	t_2d_int		player_pos_img;
	t_2d_int		dim_img;

	params.color = color;
	params.thickness = map_dim_to_pixel(game, game->img_map, 0, 0.02);
	dim.x = 0.1;
	dim.y = 0.1;
	contact = contact_with_wall(game, player);
	player_pos_img = map_pos_to_pixel(game, game->img_map, player->pos);
	dim_img = map_size_to_pixel(game, game->img_map, dim);
	impact_img = map_pos_to_pixel(game, game->img_map, contact.impact);
	draw_rectangle_from_center(game->img_map, color, &impact_img, &dim_img);
	draw_line(game->img_map, &params, &player_pos_img, &impact_img);
}

void		draw_minimap(t_game *game, t_player *old_player,
							t_player *new_player)
{
	t_player	temp_player;
	double		fov;

	fov = M_PI / 4;
	draw_player(game, old_player, g_black);
	draw_fov(game, old_player, g_black);
	temp_player = *old_player;
	temp_player.angle = old_player->angle - fov / 2;
	draw_fov(game, &temp_player, g_black);
	temp_player.angle = old_player->angle + fov / 2;
	draw_fov(game, &temp_player, g_black);
	draw_walls_and_contours(game);
	draw_player(game, new_player, g_white);
	draw_fov(game, new_player, g_red);
	temp_player = *new_player;
	temp_player.angle = new_player->angle - fov / 2;
	draw_fov(game, &temp_player, g_white);
	temp_player.angle = new_player->angle + fov / 2;
	draw_fov(game, &temp_player, g_white);
	/*copy_from_buffer(game->img_map);*/
	mlx_put_image_to_window(game->conn->mlx_ptr, game->conn->win_ptr,
			game->img_map->ptr, 0, 0);
}
