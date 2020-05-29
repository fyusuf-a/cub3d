/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 13:46:43 by fyusuf-a          #+#    #+#             */
/*   Updated: 2020/05/29 17:51:41 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_map(t_map *map)
{
	int i;

	i = 0;
	while (i < map->dim.y)
	{
		free(map->grid[i]);
		i++;
	}
	free(map->grid);
	free(map);
}

static void	free_config(t_config *config)
{
	mlx_destroy_image(g_game.conn->mlx_ptr, config->texture_no);
	mlx_destroy_image(g_game.conn->mlx_ptr, config->texture_so);
	mlx_destroy_image(g_game.conn->mlx_ptr, config->texture_we);
	mlx_destroy_image(g_game.conn->mlx_ptr, config->texture_ea);
}

static void	del(void *content)
{
	free((t_2d*)content);
}

void		free_ray(t_ray *ray)
{
	/*ft_lstclear(&ray->list, del);*/
	/*free(ray);*/
}

void		free_game(void)
{
	free_map(g_game.map);
	free(g_game.player);
	free_config(g_game.config);
	free_ray(g_game.ray);
	mlx_destroy_image(g_game.conn->mlx_ptr, g_game.img_view);
	mlx_destroy_image(g_game.conn->mlx_ptr, g_game.img_map);
	mlx_destroy_window(g_game.conn->mlx_ptr, g_game.conn->win_ptr);
	free(g_game.conn->mlx_ptr);
}
