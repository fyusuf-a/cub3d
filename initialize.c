/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 15:28:47 by fyusuf-a          #+#    #+#             */
/*   Updated: 2020/04/30 13:53:02 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void initialize_color(t_color *color)
{
	color->r = -1;
	color->g = -1;
	color->b = -1;
}

void initialize_game(const char *file, t_game *game)
{
	game->player = malloc(sizeof(t_player));
	game->player->pos.x = -1;
	game->player->pos.y = -1;
	game->map = malloc(sizeof(t_map));
	game->config = malloc(sizeof(t_config));
	initialize_color(&(game->config->floor));
	initialize_color(&(game->config->ceiling));
	game->conn = malloc(sizeof(t_connection));
	if (!(game->conn->mlx_ptr = mlx_init()))
		error("mlx: Connection could not be initialized");
	parse(file, game);
	game->conn->win_ptr = mlx_new_window(game->conn->mlx_ptr, game->config->resolution.x, game->config->resolution.y, "cub3d");
}
