/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_second.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/22 20:45:34 by fyusuf-a          #+#    #+#             */
/*   Updated: 2020/04/27 14:45:36 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void
	parse_path(t_file *file, t_game *game)
{
	file->c = gobble_while_elem(file->line, file->c, " ");
	if (ft_strchr(file->line + file->c, ' '))
		parse_error(file, LINE_NB, "Space in path");
	if (!ft_strncmp(file->line, "NO ", 3))
		game->config->texture_no_path = ft_strdup(file->line + file->c);
	else if (!ft_strncmp(file->line, "SO ", 3))
		game->config->texture_so_path = ft_strdup(file->line + file->c);
	else if (!ft_strncmp(file->line, "WE ", 3))
		game->config->texture_we_path = ft_strdup(file->line + file->c);
	else if (!ft_strncmp(file->line, "EA ", 3))
		game->config->texture_ea_path = ft_strdup(file->line + file->c);
	else if (!ft_strncmp(file->line, "S ", 2))
		game->config->sprite_path = ft_strdup(file->line + file->c);
	else
		parse_error(file, LINE_NB, "Very bad error: line identifier unknown");
}

static void
	parse_color(t_file *file, t_color *color)
{
	file->c += 2;
	file->c = gobble_while_elem(file->line, file->c, " ");
	if ((color->r = parse_natural(file)) < 0 || color->r >= 255)
		parse_error(file, LINE_NB | COLUMN_NB, "Bad red component");
	file->c = gobble_while_elem(file->line, file->c, " ");
	if (file->line[file->c] != ',')
		parse_error(file, LINE_NB | COLUMN_NB, "Expected a comma");
	file->c++;
	file->c = gobble_while_elem(file->line, file->c, " ");
	if ((color->g = parse_natural(file)) < 0 || color->g >= 255)
		parse_error(file, LINE_NB | COLUMN_NB, "Bad green component");
	file->c = gobble_while_elem(file->line, file->c, " ");
	if (file->line[file->c] != ',')
		parse_error(file, LINE_NB | COLUMN_NB, "Expected a comma");
	file->c++;
	file->c = gobble_while_elem(file->line, file->c, " ");
	if ((color->b = parse_natural(file)) < 0 || color->b >= 255)
		parse_error(file, LINE_NB | COLUMN_NB, "Bad blue component");
	if (ft_strcmp(file->line + file->c, ""))
		parse_error(file, LINE_NB | COLUMN_NB, "Trailing characters");
}

static void
	parse_resolution(t_file *file, t_game *game)
{
	file->c = gobble_while_elem(file->line, file->c, " ");
	if ((game->config->resolution.x = parse_natural(file)) <= 0)
		parse_error(file, LINE_NB | COLUMN_NB, "Bad horizontal resolution");
	file->c = gobble_while_elem(file->line, file->c, " ");
	if ((game->config->resolution.y = parse_natural(file)) <= 0)
		parse_error(file, LINE_NB | COLUMN_NB, "Bad vertical resolution");
	if (ft_strcmp(file->line + file->c, ""))
		parse_error(file, LINE_NB | COLUMN_NB, "Trailing characters");
}

int
	parse_second_pass_infos(t_file *file, t_game *game)
{
	if (!ft_strcmp(file->line, ""))
		return (GNL_NOT_DONE);
	else if (!ft_strncmp(file->line, "R ", 2))
	{
		file->c += 2;
		parse_resolution(file, game);
	}
	else if (!ft_strncmp(file->line, "NO ", 3)
			|| !ft_strncmp(file->line, "SO ", 3)
			|| !ft_strncmp(file->line, "WE ", 3)
			|| !ft_strncmp(file->line, "EA ", 3)
			|| !ft_strncmp(file->line, "S ", 2))
	{
		file->c += 2;
		parse_path(file, game);
	}
	else if (!ft_strncmp(file->line, "F ", 2))
		parse_color(file, &(game->config->floor));
	else if (!ft_strncmp(file->line, "C ", 2))
		parse_color(file, &(game->config->ceiling));
	else
		return (GNL_DONE);
	return (GNL_NOT_DONE);
}

static void
	parse_second_pass_player(t_file *file, t_game *game, int i)
{
	if (file->line[file->c] == 'N')
		game->player->angle = -90.0;
	if (file->line[file->c] == 'W')
		game->player->angle = 180.0;
	if (file->line[file->c] == 'E')
		game->player->angle = 0.0;
	if (file->line[file->c] == 'S')
		game->player->angle = 90.0;
	game->map->grid[i][file->c] = VOID;
	game->player->pos.x = 0.5 + file->c;
	game->player->pos.y = 0.5 + i;
}

static int
	parse_second_pass_map(t_file *file, t_game *game)
{
	char		c;
	static int	i = 0;

	if (!file->line[0])
		return (GNL_DONE);
	while ((c = file->line[file->c]))
	{
		/*if (c == ' ')*/
			/*game->map->grid[i][file->c] = UNDEFINED;*/
		if (c == '0')
			game->map->grid[i][file->c] = VOID;
		/*if (c == '1')*/
			/*game->map->grid[i][file->c] = WALL;*/
		if (c == '2')
			game->map->grid[i][file->c] = OBJECT;
		if (ft_elem(c, "NEWS"))
		{
			if (game->player->pos.x >= 0)
				parse_error(file, 0, "Player position initialized twice");
			parse_second_pass_player(file, game, i);
		}
		file->c++;
	}
	i++;
	return (GNL_NOT_DONE);
}

void
	parse_second_pass(t_file *file, t_game *game)
{
	int i;
	int j;

	repeat_gnl(file, game, parse_second_pass_infos);
	game->map->grid = malloc(game->map->dim.y * sizeof(t_object*));
	i = 0;
	while (i < game->map->dim.y)
	{
		game->map->grid[i] = malloc(game->map->dim.x * sizeof(t_object));
		j = 0;
		while (j < game->map->dim.x)
		{
			game->map->grid[i][j] = WALL;
			j++;
		}
		i++;
	}
	repeat_gnl(file, game, parse_second_pass_map);
}
