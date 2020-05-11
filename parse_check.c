/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 13:28:32 by fyusuf-a          #+#    #+#             */
/*   Updated: 2020/05/11 16:18:24 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	recursive_check(const t_file *file, t_map *map, int x, int y)
{
	if (map->grid[y][x] == VOID || map->grid[y][x] == OBJECT)
	{
		map->grid[y][x] = WALL;
		if (x - 1 < 0)
			parse_error(file, 0, "Map is not closed on the left "
					"at position x = %d, y = %d", x, y);
		recursive_check(file, map, x - 1, y);
		if (x + 1 >= map->dim.x)
			parse_error(file, 0, "Map is not closed on the right "
					"at position x = %d, y = %d", x, y);
		recursive_check(file, map, x + 1, y);
		if (y - 1 < 0)
			parse_error(file, 0, "Map is not closed above at position "
					"x = %d, y = %d", x, y);
		recursive_check(file, map, x, y - 1);
		if (y + 1 >= map->dim.y)
			parse_error(file, 0, "Map is not closed below at position "
					"x = %d, y = %d", x, y);
		recursive_check(file, map, x, y + 1);
	}
}

static void	check_if_exist(const t_file *file, const t_game *game)
{
	if (game->map->dim.x == 0)
		parse_error(file, 0, "Map is undefined");
	if (game->player->pos.x == -1)
		parse_error(file, 0, "Player position is undefined");
	if (!game->config->resolution.x)
		parse_error(file, 0, "Resolution is undefined");
	if (!game->config->texture_no_path)
		parse_error(file, 0, "North texture is undefined");
	if (!game->config->texture_so_path)
		parse_error(file, 0, "South texture is undefined");
	if (!game->config->texture_we_path)
		parse_error(file, 0, "West texture is undefined");
	if (!game->config->texture_ea_path)
		parse_error(file, 0, "East texture is undefined");
	if (!game->config->sprite_path)
		parse_error(file, 0, "Sprite texture is undefined");
	if (game->config->floor.r == -1)
		parse_error(file, 0, "Floor color is undefined");
	if (game->config->ceiling.r == -1)
		parse_error(file, 0, "Ceiling color is undefined");
}

void		parse_check(const t_file *file, const t_game *game)
{
	t_map	copy;
	int		i;
	int		j;

	check_if_exist(file, game);
	if (!(copy.grid = malloc(game->map->dim.y * sizeof(t_object*))))
		error("parse_check: malloc failed");
	i = 0;
	while (i < game->map->dim.y)
	{
		if (!(copy.grid[i] = malloc(game->map->dim.x * sizeof(t_object))))
			error("parse_check: malloc failed");
		j = 0;
		while (j < game->map->dim.x)
		{
			copy.grid[i][j] = game->map->grid[i][j];
			j++;
		}
		i++;
	}
	copy.dim.x = game->map->dim.x;
	copy.dim.y = game->map->dim.y;
	recursive_check(file, &copy, game->player->pos.x, game->player->pos.y);
}
