/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 15:29:13 by fyusuf-a          #+#    #+#             */
/*   Updated: 2020/06/29 23:07:29 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double		map_dim_to_pixel(t_image *image, int axis, double x)
{
	if (axis == YAXIS)
		return (x / g_game.map.dim.y * image->res.y);
	return (x / g_game.map.dim.x * image->res.x);
}

t_2d_int	map_size_to_pixel(t_image *image, t_2d size)
{
	t_2d_int	ret;

	ret.x = map_dim_to_pixel(image, XAXIS, size.x);
	ret.y = map_dim_to_pixel(image, YAXIS, size.y);
	return (ret);
}

t_2d_int	map_pos_to_pixel(t_image *image, t_2d pos)
{
	pos.x = pos.x + 0.5;
	pos.y = pos.y + 0.5;
	return (map_size_to_pixel(image, pos));
}

void		draw_fov(const t_player *player, int hide)
{
	t_2d			dim;
	t_line_params	params;
	t_2d_int		impact_img;
	t_2d_int		player_pos_img;
	t_2d_int		dim_img;

	params.color = hide ? 0 : g_game.map_color;
	params.thickness = map_dim_to_pixel(g_game.img_map, 0, 0.02);
	dim.x = 0.1;
	dim.y = 0.1;
	g_game.ray = contact_with_wall(player, &g_iter);
	player_pos_img = map_pos_to_pixel(g_game.img_map, player->pos);
	dim_img = map_size_to_pixel(g_game.img_map, dim);
	impact_img = map_pos_to_pixel(g_game.img_map,
							((t_contact*)(g_game.ray->content))->impact);
	draw_rectangle_from_center(g_game.img_map,
			hide ? 0 : g_game.map_color, impact_img, dim_img);
	draw_line(g_game.img_map, &params, player_pos_img, impact_img);
}

void		draw_minimap(t_player *old_player, t_player *new_player)
{
	t_player	temp_player;
	double		fov;

	fov = M_PI / 4;
	draw_player(old_player, 1);
	draw_fov(old_player, 1);
	temp_player = *old_player;
	temp_player.angle = old_player->angle - fov / 2;
	draw_fov(&temp_player, 1);
	temp_player.angle = old_player->angle + fov / 2;
	draw_fov(&temp_player, 1);
	draw_walls_and_contours();
	draw_player(new_player, 0);
	draw_fov(new_player, 0);
	temp_player = *new_player;
	temp_player.angle = new_player->angle - fov / 2;
	draw_fov(&temp_player, 0);
	temp_player.angle = new_player->angle + fov / 2;
	draw_fov(&temp_player, 0);
	print_minimap();
}
