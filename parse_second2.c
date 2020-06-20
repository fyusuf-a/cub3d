/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_second2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 16:19:57 by fyusuf-a          #+#    #+#             */
/*   Updated: 2020/06/20 11:18:25 by fyusuf-a         ###   ########.fr       */
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
		if (c == '0')
			g_game.map.grid[i][file->c] = VOID;
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

void
	parse_color(t_file *file, t_color *color)
{
	file->c += 2;
	file->c = gobble_while_elem(file->line, file->c, " ");
	if ((color->r = parse_natural(file)) < 0 || color->r > 255)
		parse_error(file, LINE_NB | COLUMN_NB, "Bad red component");
	file->c = gobble_while_elem(file->line, file->c, " ");
	if (file->line[file->c] != ',')
		parse_error(file, LINE_NB | COLUMN_NB, "Expected a comma");
	file->c++;
	file->c = gobble_while_elem(file->line, file->c, " ");
	if ((color->g = parse_natural(file)) < 0 || color->g > 255)
		parse_error(file, LINE_NB | COLUMN_NB, "Bad green component");
	file->c = gobble_while_elem(file->line, file->c, " ");
	if (file->line[file->c] != ',')
		parse_error(file, LINE_NB | COLUMN_NB, "Expected a comma");
	file->c++;
	file->c = gobble_while_elem(file->line, file->c, " ");
	if ((color->b = parse_natural(file)) < 0 || color->b > 255)
		parse_error(file, LINE_NB | COLUMN_NB, "Bad blue component");
	if (ft_strcmp(file->line + file->c, ""))
		parse_error(file, LINE_NB | COLUMN_NB, "Trailing characters");
}
