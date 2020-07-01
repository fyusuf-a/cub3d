/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_first.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 16:45:47 by fyusuf-a          #+#    #+#             */
/*   Updated: 2020/07/01 12:27:28 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int
	parse_first_pass_infos(t_file *file)
{
	if (!ft_strcmp(file->line, "")
		|| !ft_strncmp(file->line, "R ", 2)
		|| !ft_strncmp(file->line, "NO ", 3)
		|| !ft_strncmp(file->line, "SO ", 3)
		|| !ft_strncmp(file->line, "WE ", 3)
		|| !ft_strncmp(file->line, "EA ", 3)
		|| !ft_strncmp(file->line, "S ", 2)
		|| !ft_strncmp(file->line, "F ", 2)
		|| !ft_strncmp(file->line, "C ", 2))
		return (GNL_NOT_DONE);
	return (GNL_DONE);
}

static int
	parse_first_pass_map(t_file *file)
{
	char	c;

	if (!file->line[0])
		return (GNL_DONE);
	while ((c = file->line[file->c]))
	{
		if (!ft_elem(c, "012NEWS "))
			parse_error(file, LINE_NB | COLUMN_NB,
					"Unauthorized character '%c'", c);
		file->c++;
	}
	if (file->c > g_game.map.dim.x)
		g_game.map.dim.x = file->c;
	g_game.map.dim.y++;
	return (GNL_NOT_DONE);
}

static int
	parse_first_pass_eof(t_file *file)
{
	static int	first = 1;

	(void)file;
	if (first)
	{
		first = 0;
		return (GNL_NOT_DONE);
	}
	parse_error(file, LINE_NB, "Extraneous line after map");
	first = 1;
	return (GNL_DONE);
}

void
	allocate_map(void)
{
	int i;
	int j;

	if (!(g_game.map.grid = malloc(g_game.map.dim.y * sizeof(t_object*))))
		error("allocate_map: malloc failed");
	i = 0;
	while (i < g_game.map.dim.y)
	{
		if (!(g_game.map.grid[i] =
					malloc(g_game.map.dim.x * sizeof(t_object))))
		{
			while (i >= 0)
				free(g_game.map.grid[i--]);
			free(g_game.map.grid);
			error("allocate_map: malloc failed");
		}
		j = 0;
		while (j < g_game.map.dim.x)
		{
			g_game.map.grid[i][j] = VOID;
			j++;
		}
		i++;
	}
	g_game.map.allocated = 1;
}

void
	parse_first_pass(t_file *file)
{
	if (repeat_gnl(file, parse_first_pass_infos) == GNL_FILE_END)
		parse_error(file, LINE_NB | COLUMN_NB, "eof before map");
	if (repeat_gnl(file, parse_first_pass_map) != GNL_FILE_END)
		repeat_gnl(file, parse_first_pass_eof);
	allocate_map();
	free(file->line);
}
