/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 16:08:01 by fyusuf-a          #+#    #+#             */
/*   Updated: 2020/05/18 16:01:31 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		draw_contours_if_void(t_game *game, t_2d center, int i, int j)
{
	t_2d			point1;
	t_2d			point2;
	t_line_params	params;

	if (game->map->grid[i][j] == VOID)
	{
		point1.x = center.x - 0.5;
		point1.y = center.y + 0.5;
		point2.x = center.x + 0.5;
		point2.y = center.y + 0.5;
		params.color = g_white;
		params.thickness = map_dim_to_pixel(game, game->img_map,
												0, 0.01);
		draw_line(game->img_map, &params,
			map_pos_to_pixel(game, game->img_map, point1),
			map_pos_to_pixel(game, game->img_map, point2));
		point1.x = center.x + 0.5;
		point1.y = center.y - 0.5;
		draw_line(game->img_map, &params,
			map_pos_to_pixel(game, game->img_map, point1),
			map_pos_to_pixel(game, game->img_map, point2));
	}
}

static void		draw_if_wall(t_game *game, t_2d center, int i, int j)
{
	t_2d	square_dim;

	square_dim.x = 1.0;
	square_dim.y = 1.0;
	if (game->map->grid[i][j] == WALL)
	{
		draw_rectangle_from_center(game->img_map, g_white,
			map_pos_to_pixel(game, game->img_map, center),
			map_size_to_pixel(game, game->img_map, square_dim));
	}
}

void			draw_walls_and_contours(t_game *game)
{
	int		i;
	int		j;
	t_2d	center;

	i = 0;
	while (i < game->map->dim.y)
	{
		j = 0;
		while (j < game->map->dim.x)
		{
			center.x = j;
			center.y = i;
			draw_if_wall(game, center, i, j);
			draw_contours_if_void(game, center, i, j);
			j++;
		}
		i++;
	}
}

void			draw_player(t_game *game, t_player *player, t_color color)
{
	t_2d		dim;

	dim.x = 0.05;
	dim.y = 0.05;
	draw_rectangle_from_center(game->img_map, color,
			map_pos_to_pixel(game, game->img_map, player->pos),
			map_size_to_pixel(game, game->img_map, dim));
}
