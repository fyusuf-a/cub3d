/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 13:28:32 by fyusuf-a          #+#    #+#             */
/*   Updated: 2020/06/29 20:39:49 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void
	recursive_check(const t_file *file, t_map *map, int x, int y)
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

static void
	check_if_exist(const t_file *file)
{
	if (g_game.map.dim.x == 0)
		parse_error(file, 0, "Map is undefined");
	if (g_game.player.pos.x == -1)
		parse_error(file, 0, "Player position is undefined");
	if (!g_game.config.resolution.x)
		parse_error(file, 0, "Resolution is undefined");
	if (g_game.config.floor == -1)
		parse_error(file, 0, "Floor color is undefined");
	if (g_game.config.ceiling == -1)
		parse_error(file, 0, "Ceiling color is undefined");
}

static void
	free_grid(t_map *copy)
{
	int	i;

	i = 0;
	while (i < g_game.map.dim.y)
	{
		free(copy->grid[i]);
		i++;
	}
	free(copy->grid);
}

void
	parse_check(const t_file *file)
{
	t_map	copy;
	int		i;
	int		j;

	check_if_exist(file);
	if (!(copy.grid = malloc(g_game.map.dim.y * sizeof(t_object*))))
		error("parse_check: malloc failed");
	i = 0;
	while (i < g_game.map.dim.y)
	{
		if (!(copy.grid[i] = malloc(g_game.map.dim.x * sizeof(t_object))))
			error("parse_check: malloc failed");
		j = 0;
		while (j < g_game.map.dim.x)
		{
			copy.grid[i][j] = g_game.map.grid[i][j];
			j++;
		}
		i++;
	}
	copy.dim.x = g_game.map.dim.x;
	copy.dim.y = g_game.map.dim.y;
	recursive_check(file, &copy, g_game.player.pos.x, g_game.player.pos.y);
	free_grid(&copy);
}
