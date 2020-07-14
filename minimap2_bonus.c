/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap2_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 16:08:01 by fyusuf-a          #+#    #+#             */
/*   Updated: 2020/07/14 11:40:28 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void
	draw_contours(t_2d center)
{
	t_2d			point1;
	t_2d			point2;
	t_2d_int		point1_img;
	t_2d_int		point2_img;
	t_line_params	params;

	point1.x = center.x - 0.5;
	point1.y = center.y + 0.5;
	point2.x = center.x + 0.5;
	point2.y = center.y + 0.5;
	params.color = g_game.map_color;
	params.thickness = map_dim_to_pixel(g_game.img_map,
											0, 0.01);
	point1_img = map_pos_to_pixel(g_game.img_map, point1);
	point2_img = map_pos_to_pixel(g_game.img_map, point2);
	draw_line(g_game.img_map, &params, point1_img, point2_img);
	point1.x = center.x + 0.5;
	point1.y = center.y - 0.5;
	point1_img = map_pos_to_pixel(g_game.img_map, point1);
	draw_line(g_game.img_map, &params, point1_img, point2_img);
}

static void
	draw_wall(t_2d center)
{
	t_2d		square_dim;
	t_2d_int	square_dim_img;
	t_2d_int	center_img;

	center_img = map_pos_to_pixel(g_game.img_map, center);
	square_dim.x = 1.0;
	square_dim.y = 1.0;
	square_dim_img = map_size_to_pixel(g_game.img_map, square_dim);
	draw_rectangle_from_center(g_game.img_map, g_game.map_color, center_img,
				square_dim_img);
}

static void
	draw_sprite(t_2d center)
{
	t_2d		square_dim;
	t_2d_int	square_dim_img;
	t_2d_int	center_img;

	center_img = map_pos_to_pixel(g_game.img_map, center);
	square_dim.x = 0.5;
	square_dim.y = 0.5;
	square_dim_img = map_size_to_pixel(g_game.img_map, square_dim);
	draw_rectangle_from_center(g_game.img_map, g_game.map_color, center_img,
				square_dim_img);
}

void
	draw_walls_and_contours(void)
{
	int			i;
	int			j;
	t_2d		center;
	t_object	current;

	i = 0;
	while (i < g_game.map.dim.y)
	{
		j = 0;
		while (j < g_game.map.dim.x)
		{
			center.x = j;
			center.y = i;
			current = g_game.map.grid[i][j];
			if (current == WALL)
				draw_wall(center);
			if (current == OBJECT)
				draw_sprite(center);
			if (current == VOID || current == OBJECT)
				draw_contours(center);
			j++;
		}
		i++;
	}
}

void
	draw_player(t_player *player, int hide)
{
	t_2d_int	player_pos_img;
	t_2d		dim;
	t_2d_int	dim_img;

	dim.x = 0.1;
	dim.y = 0.1;
	player_pos_img = map_pos_to_pixel(g_game.img_map, player->pos);
	dim_img = map_size_to_pixel(g_game.img_map, dim);
	draw_rectangle_from_center(g_game.img_map, hide ? 0 : g_game.map_color,
			player_pos_img, dim_img);
}
