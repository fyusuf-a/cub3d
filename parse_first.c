/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_first.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 16:45:47 by fyusuf-a          #+#    #+#             */
/*   Updated: 2020/04/30 13:40:50 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int
	parse_first_pass_infos(t_file *file, t_game *game)
{
	(void)game;
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
	parse_first_pass_map(t_file *file, t_game *game)
{
	char	c;

	if (!file->line[0])
		return (GNL_DONE);
	while ((c = file->line[file->c]))
	{
		if (!ft_elem(c, "012NEWS "))
			parse_error(file, LINE_NB || COLUMN_NB,
					"Unauthorized character '%c'", c);
		file->c++;
	}
	if (file->c > game->map->dim.x)
		game->map->dim.x = file->c;
	game->map->dim.y++;
	return (GNL_NOT_DONE);
}

static int
	parse_first_pass_eof(t_file *file, t_game *game)
{
	static int	first = 1;

	(void)game;
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
	parse_first_pass(t_file *file, t_game *game)
{
	repeat_gnl(file, game, parse_first_pass_infos);
	repeat_gnl(file, game, parse_first_pass_map);
	repeat_gnl(file, game, parse_first_pass_eof);
}

void
	parse(const char *path, t_game *game)
{
	t_file	*file;
	char	*needle;

	file = open_file(path);
	if (!(needle = ft_strrchr(path, '.')))
		error("%s: File extension should be .cub", path);
	if (ft_strcmp(needle, ".cub") != 0)
		error("%s: File extension should be .cub", path);
	parse_first_pass(file, game);
	close_file(file);
	file = open_file(path);
	parse_second_pass(file, game);
	parse_check(file, game);
	close_file(file);
}
