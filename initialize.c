/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 15:28:47 by fyusuf-a          #+#    #+#             */
/*   Updated: 2020/05/24 23:49:34 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		initialize_color(t_color *color)
{
	color->r = -1;
	color->g = -1;
	color->b = -1;
}

static t_image	*initialize_minimap(t_game *game)
{
	t_2d_int	res;
	t_image		*ret;

	if (game->map->dim.x < game->map->dim.y)
	{
		res.y = game->config->resolution.y;
		res.x = res.y / game->map->dim.y * game->map->dim.x;
	}
	else
	{
		res.x = game->config->resolution.x;
		res.y = res.x / game->map->dim.x * game->map->dim.y;
	}
	res.x /= 3;
	res.y /= 3;
	ret = initialize_image(game, res, 255);
	/*ret->buffered = 1;*/
	return (ret);
}

void			initialize_config(t_game *game)
{
	if (!(game->config = malloc(sizeof(t_config))))
		error("malloc: could not allocate config");
	if (!(game->config->texture_no = malloc(sizeof(t_image))))
		error("malloc: could not allocate image");
	if (!(game->config->texture_so = malloc(sizeof(t_image))))
		error("malloc: could not allocate image");
	if (!(game->config->texture_we = malloc(sizeof(t_image))))
		error("malloc: could not allocate image");
	if (!(game->config->texture_ea = malloc(sizeof(t_image))))
		error("malloc: could not allocate image");
}

void			initialize_game(const char *file, t_game *game)
{
	if (!(game->player = malloc(sizeof(t_player))))
		error("initialize_game: could not allocate player");
	game->player->pos.x = -1;
	game->player->pos.y = -1;
	if (!(game->map = malloc(sizeof(t_map))))
		error("initialize_game: could not allocate map");
	initialize_config(game);
	initialize_color(&(game->config->floor));
	initialize_color(&(game->config->ceiling));
	if (!(game->conn = malloc(sizeof(t_connection))))
		error("initialize_game: could not allocate connection");
	if (!(game->conn->mlx_ptr = mlx_init()))
		error("mlx: Connection could not be initialized");
	parse(file, game);
	game->conn->win_ptr = mlx_new_window(game->conn->mlx_ptr,
			game->config->resolution.x, game->config->resolution.y, "cub3d");
	game->img_view = initialize_image(game, game->config->resolution, 0);
	game->img_map = initialize_minimap(game);
}
