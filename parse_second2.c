/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_second2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 16:19:57 by fyusuf-a          #+#    #+#             */
/*   Updated: 2020/05/13 10:43:13 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void
	parse_second_pass_player(t_file *file, t_game *game, int i)
{
	if (file->line[file->c] == 'N')
		game->player->angle = -M_PI / 2;
	if (file->line[file->c] == 'W')
		game->player->angle = M_PI;
	if (file->line[file->c] == 'E')
		game->player->angle = 0;
	if (file->line[file->c] == 'S')
		game->player->angle = M_PI / 2;
	game->map->grid[i][file->c] = VOID;
	game->player->pos.x = file->c;
	game->player->pos.y = i;
}

int
	parse_second_pass_map(t_file *file, t_game *game)
{
	char		c;
	static int	i = 0;

	if (!file->line[0])
		return (GNL_DONE);
	while ((c = file->line[file->c]))
	{
		if (c == '0')
			game->map->grid[i][file->c] = VOID;
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
