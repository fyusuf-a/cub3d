/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 15:28:47 by fyusuf-a          #+#    #+#             */
/*   Updated: 2020/05/18 16:13:25 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		initialize_color(t_color *color)
{
	color->r = -1;
	color->g = -1;
	color->b = -1;
}

static t_image	*initialize_image(t_game *game, t_2d_int res, int alpha)
{
	int		size_line;
	t_image	*ret;
	int		i;

	if (alpha < 0 || alpha > 255)
		error("initialize_image: Incorrect value %d for alpha.", alpha);
	ret = malloc(sizeof(t_image));
	ret->res = res;
	ret->ptr = mlx_new_image(game->conn->mlx_ptr, res.x, res.y);
	ret->data = mlx_get_data_addr(ret->ptr, &(ret->bpp), &size_line,
			&(ret->endian));
	ret->bpp /= 8;
	if (size_line != ret->res.x * ret->bpp)
	{
		error("initialize_game: unexpected size %d which is not equal to the "
				"horizontal resolution %d times the number of bytes per pixel "
				"%d in map image", size_line,
				ret->res.x, ret->bpp);
	}
	i = 0;
	if (ret->bpp > 3)
		while (i < ret->res.x * ret->res.y)
		{
			ret->data[i * ret->bpp + 3] = alpha;
			i++;
		}
	if (!(ret->buffer = malloc(ret->bpp * ret->res.x * ret->res.y)))
		error("initialize_image: malloc failed");
	return (ret);
}

static void		initialize_minimap(t_game *game)
{
	t_2d_int	res;

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
	game->img_map = initialize_image(game, res, 127);
	game->img_map->buffered = 1;
}

void			initialize_game(const char *file, t_game *game)
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
	game->conn->win_ptr = mlx_new_window(game->conn->mlx_ptr,
			game->config->resolution.x, game->config->resolution.y, "cub3d");
	initialize_minimap(game);
}
