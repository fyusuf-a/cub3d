/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_second2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 16:19:57 by fyusuf-a          #+#    #+#             */
/*   Updated: 2020/07/01 19:26:39 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void
	parse_second_pass_player(t_file *file, int i)
{
	if (file->line[file->c] == 'N')
		g_game.player.angle = -M_PI / 2;
	if (file->line[file->c] == 'W')
		g_game.player.angle = M_PI;
	if (file->line[file->c] == 'E')
		g_game.player.angle = 0;
	if (file->line[file->c] == 'S')
		g_game.player.angle = M_PI / 2;
	g_game.map.grid[i][file->c] = VOID;
	g_game.player.pos.x = file->c;
	g_game.player.pos.y = i;
}

int
	parse_second_pass_map(t_file *file)
{
	char		c;
	static int	i = 0;

	if (!file->line[0])
		return (GNL_DONE);
	while ((c = file->line[file->c]))
	{
		if (c == '1')
			g_game.map.grid[i][file->c] = WALL;
		if (c == '2')
			g_game.map.grid[i][file->c] = OBJECT;
		if (ft_elem(c, "NEWS"))
		{
			if (g_game.player.pos.x >= 0)
				parse_error(file, 0, "Player position initialized twice");
			parse_second_pass_player(file, i);
		}
		file->c++;
	}
	i++;
	return (GNL_NOT_DONE);
}

static int
	parse_color_acc(t_file *file)
{
	int ret;

	file->c = gobble_while_elem(file->line, file->c, " ");
	if ((ret = parse_natural(file)) < 0 || ret > 255)
		parse_error(file, LINE_NB | COLUMN_NB, "Bad color component");
	file->c = gobble_while_elem(file->line, file->c, " ");
	return (ret);
}

void
	parse_color(t_file *file, int32_t *color)
{
	if (*color != -1)
		parse_error(file, LINE_NB, "Color defined twice");
	file->c += 2;
	file->c = gobble_while_elem(file->line, file->c, " ");
	*color = parse_color_acc(file) << 16;
	if (file->line[file->c++] != ',')
		parse_error(file, LINE_NB | COLUMN_NB, "Expected a comma");
	file->c = gobble_while_elem(file->line, file->c, " ");
	*color += parse_color_acc(file) << 8;
	if (file->line[file->c++] != ',')
		parse_error(file, LINE_NB | COLUMN_NB, "Expected a comma");
	file->c = gobble_while_elem(file->line, file->c, " ");
	*color += parse_color_acc(file);
	if (ft_strcmp(file->line + file->c, ""))
		parse_error(file, LINE_NB | COLUMN_NB, "Trailing characters");
}
