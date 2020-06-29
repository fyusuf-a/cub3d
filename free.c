/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 13:46:43 by fyusuf-a          #+#    #+#             */
/*   Updated: 2020/06/29 17:52:30 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void
	free_map(t_map *map)
{
	int i;

	if (map->allocated)
	{
		i = 0;
		while (i < map->dim.y)
		{
			if (map->grid[i])
				free(map->grid[i]);
			i++;
		}
	}
	if (map->grid)
		free(map->grid);
}

static void
	free_image(t_image *image)
{
	if (image->ptr)
		mlx_destroy_image(g_game.conn.mlx_ptr, image->ptr);
	/*if (image->buffer)*/
		/*free(image->buffer);*/
	free(image);
}

static void
	free_config(t_config *config)
{
	if (config->texture_no)
		free_image(config->texture_no);
	if (config->texture_so)
		free_image(config->texture_so);
	if (config->texture_we)
		free_image(config->texture_we);
	if (config->texture_ea)
		free_image(config->texture_ea);
	if (config->texture_sprite)
		free_image(config->texture_sprite);
}

static void
	free_img_map_img_view_conn(void)
{
	if (g_game.conn.mlx_ptr)
	{
		mlx_do_key_autorepeaton(g_game.conn.mlx_ptr);
		if (g_game.img_map)
		{
			mlx_destroy_image(g_game.conn.mlx_ptr, g_game.img_map->ptr);
			free(g_game.img_map);
		}
		if (g_game.img_view)
		{
			mlx_destroy_image(g_game.conn.mlx_ptr, g_game.img_view->ptr);
			free(g_game.img_view);
		}
		if (g_game.conn.win_ptr)
			mlx_destroy_window(g_game.conn.mlx_ptr, g_game.conn.win_ptr);
	}
}

void
	free_game()
{
	free_map(&g_game.map);
	free_config(&g_game.config);
	if (g_game.ray)
		free_ray(g_game.ray);
	free_img_map_img_view_conn();
}
	

int
	free_and_exit_game()
{
	free_game();
	return (EXIT_SUCCESS);
}
