/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_second.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/22 20:45:34 by fyusuf-a          #+#    #+#             */
/*   Updated: 2020/07/14 11:49:11 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	parse_texture(t_file *file, t_image **img)
{
	if (*img)
		parse_error(file, LINE_NB, "Texture defined twice");
	*img = NULL;
	*img = initialize_texture(file->line + file->c);
}

static void	parse_path(t_file *file)
{
	file->c = gobble_while_elem(file->line, file->c, " ");
	if (!ft_strncmp(file->line, "NO ", 3))
		parse_texture(file, &g_game.config.texture_no);
	else if (!ft_strncmp(file->line, "SO ", 3))
		parse_texture(file, &g_game.config.texture_so);
	else if (!ft_strncmp(file->line, "WE ", 3))
		parse_texture(file, &g_game.config.texture_we);
	else if (!ft_strncmp(file->line, "EA ", 3))
		parse_texture(file, &g_game.config.texture_ea);
	else if (!ft_strncmp(file->line, "S ", 2))
		parse_texture(file, &g_game.config.texture_sprite);
	else
		parse_error(file, LINE_NB, "Very bad error: line identifier unknown");
}

static void	parse_resolution(t_file *file)
{
	int temp;

	if (!(g_game.config.resolution.x == -1))
		parse_error(file, LINE_NB, "Resolution defined twice");
	mlx_get_screen_size(g_game.conn.mlx_ptr, &g_game.config.resolution.x,
			&g_game.config.resolution.y);
	file->c = gobble_while_elem(file->line, file->c, " ");
	if ((temp = parse_natural(file)) <= 0)
		parse_error(file, LINE_NB | COLUMN_NB, "Bad horizontal resolution");
	g_game.config.resolution.x = ft_min(g_game.config.resolution.x, temp);
	file->c = gobble_while_elem(file->line, file->c, " ");
	if ((temp = parse_natural(file)) <= 0)
		parse_error(file, LINE_NB | COLUMN_NB, "Bad vertical resolution");
	g_game.config.resolution.y = ft_min(g_game.config.resolution.y, temp);
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
		parse_color(file, &(g_game.config.floor));
	else if (!ft_strncmp(file->line, "C ", 2))
		parse_color(file, &(g_game.config.ceiling));
	else
		return (GNL_DONE);
	return (GNL_NOT_DONE);
}

void		parse_second_pass(t_file *file)
{
	repeat_gnl(file, parse_second_pass_infos);
	repeat_gnl(file, parse_second_pass_map);
	free(file->line);
}
