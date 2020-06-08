/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_second.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/22 20:45:34 by fyusuf-a          #+#    #+#             */
/*   Updated: 2020/06/08 18:52:43 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	parse_texture(t_file *file, t_image **image)
{
	if (*image)
		parse_error(file, LINE_NB, "Texture defined twice");
	*image = initialize_texture(file->line + file->c);
}

static void	parse_path(t_file *file)
{
	file->c = gobble_while_elem(file->line, file->c, " ");
	if (ft_strchr(file->line + file->c, ' '))
		parse_error(file, LINE_NB, "Space in path");
	if (!ft_strncmp(file->line, "NO ", 3))
		parse_texture(file, &g_game.config->texture_no);
	else if (!ft_strncmp(file->line, "SO ", 3))
		parse_texture(file, &g_game.config->texture_so);
	else if (!ft_strncmp(file->line, "WE ", 3))
		parse_texture(file, &g_game.config->texture_we);
	else if (!ft_strncmp(file->line, "EA ", 3))
		parse_texture(file, &g_game.config->texture_ea);
	else if (!ft_strncmp(file->line, "S ", 2))
		parse_texture(file, &g_game.config->texture_sprite);
	else
		parse_error(file, LINE_NB, "Very bad error: line identifier unknown");
}

static void	parse_resolution(t_file *file)
{
	file->c = gobble_while_elem(file->line, file->c, " ");
	if ((g_game.config->resolution.x = parse_natural(file)) <= 0)
		parse_error(file, LINE_NB | COLUMN_NB, "Bad horizontal resolution");
	file->c = gobble_while_elem(file->line, file->c, " ");
	if ((g_game.config->resolution.y = parse_natural(file)) <= 0)
		parse_error(file, LINE_NB | COLUMN_NB, "Bad vertical resolution");
	if (ft_strcmp(file->line + file->c, ""))
		parse_error(file, LINE_NB | COLUMN_NB, "Trailing characters");
}

static int	parse_second_pass_infos(t_file *file)
{
	if (!ft_strcmp(file->line, ""))
		return (GNL_NOT_DONE);
	else if (!ft_strncmp(file->line, "R ", 2))
	{
		file->c += 2;
		parse_resolution(file);
	}
	else if (!ft_strncmp(file->line, "NO ", 3)
			|| !ft_strncmp(file->line, "SO ", 3)
			|| !ft_strncmp(file->line, "WE ", 3)
			|| !ft_strncmp(file->line, "EA ", 3)
			|| !ft_strncmp(file->line, "S ", 2))
	{
		file->c += 2;
		parse_path(file);
	}
	else if (!ft_strncmp(file->line, "F ", 2))
		parse_color(file, &(g_game.config->floor));
	else if (!ft_strncmp(file->line, "C ", 2))
		parse_color(file, &(g_game.config->ceiling));
	else
		return (GNL_DONE);
	return (GNL_NOT_DONE);
}

void		parse_second_pass(t_file *file)
{
	int i;
	int j;

	repeat_gnl(file, parse_second_pass_infos);
	g_game.map->grid = malloc(g_game.map->dim.y * sizeof(t_object*));
	i = 0;
	while (i < g_game.map->dim.y)
	{
		g_game.map->grid[i] = malloc(g_game.map->dim.x * sizeof(t_object));
		j = 0;
		while (j < g_game.map->dim.x)
		{
			g_game.map->grid[i][j] = WALL;
			j++;
		}
		i++;
	}
	repeat_gnl(file, parse_second_pass_map);
	free(file->line);
}
