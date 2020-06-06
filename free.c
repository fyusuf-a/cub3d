/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 13:46:43 by fyusuf-a          #+#    #+#             */
/*   Updated: 2020/06/01 11:47:52 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_map(t_map *map)
{
	int i;

	i = 0;
	while (i < map->dim.y)
	{
		if (map->grid[i])
			free(map->grid[i]);
		i++;
	}
	if (map->grid)
		free(map->grid);
	free(map);
}

static void	free_config(t_config *config)
{
	if (config->texture_no)
		mlx_destroy_image(g_game.conn->mlx_ptr, config->texture_no);
	if (config->texture_so)
		mlx_destroy_image(g_game.conn->mlx_ptr, config->texture_so);
	if (config->texture_we)
		mlx_destroy_image(g_game.conn->mlx_ptr, config->texture_we);
	if (config->texture_ea)
		mlx_destroy_image(g_game.conn->mlx_ptr, config->texture_ea);
	if (config->texture_sprite)
		mlx_destroy_image(g_game.conn->mlx_ptr, config->texture_sprite);
	free(config);
}

static void	free_ray(t_list *ray)
{
	ft_lstclear(&ray, del);
	free(ray);
}

static void	free_conn(t_connection *conn)
{
	mlx_destroy_window(conn->mlx_ptr, conn->win_ptr);
	free(conn->win_ptr);
}

void		free_game(void)
{
	if (g_game.map)
		free_map(g_game.map);
	if (g_game.player)
		free(g_game.player);
	if (g_game.config)
		free_config(g_game.config);
	if (g_game.ray)
		free_ray(g_game.ray);
	if (g_game.img_view)
		mlx_destroy_image(g_game.conn->mlx_ptr, g_game.img_view);
	if (g_game.img_map)
		mlx_destroy_image(g_game.conn->mlx_ptr, g_game.img_map);
	if (g_game.conn)
		free_conn(g_game.conn);
}
