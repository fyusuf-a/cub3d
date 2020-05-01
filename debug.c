/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/19 15:15:55 by fyusuf-a          #+#    #+#             */
/*   Updated: 2020/05/01 14:54:56 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_config(const t_config *c)
{
	ft_printf("Resolution is %dx%d\n", c->resolution.x, c->resolution.y);
	ft_printf("Path to north texture is \"%s\"\n", c->texture_no_path);
	ft_printf("Path to south texture is \"%s\"\n", c->texture_so_path);
	ft_printf("Path to west texture is \"%s\"\n", c->texture_we_path);
	ft_printf("Path to east texture is \"%s\"\n", c->texture_ea_path);
	ft_printf("Path to sprite texture is \"%s\"\n", c->sprite_path);
	ft_printf("Color for floor is %d,%d,%d\n", c->floor.r, c->floor.g,
			c->floor.b);
	ft_printf("Color for ceiling is %d,%d,%d\n", c->ceiling.r, c->ceiling.g,
			c->ceiling.b);
}

void	print_map(const t_map *m)
{
	int	i;
	int	j;

	while (i < m->dim.y)
	{
		while (j < m->dim.x)
		{
			if (m->grid[i][j] == VOID)
				ft_printf("0");
			else if (m->grid[i][j] == WALL)
				ft_printf("1");
			else if (m->grid[i][j] == OBJECT)
				ft_printf("2");
			else
				ft_printf(" ");
			j++;
		}
		ft_printf("\n");
		i++;
	}
}

void	print_player(const t_player *p)
{
	ft_printf("x = %f, y = %f, alpha = %f\n", p->pos.x, p->pos.y, p->angle);
}
