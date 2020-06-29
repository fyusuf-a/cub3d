/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 21:01:54 by fyusuf-a          #+#    #+#             */
/*   Updated: 2020/06/29 22:51:14 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_minimap(void)
{
	t_2d_int	pos;
	int			color;

	pos.y = 0;
	while (pos.y < g_game.img_map->res.y)
	{
		pos.x = 0;
		while (pos.x < g_game.img_map->res.x)
		{
			color = *((int*)(g_game.img_map->data
				+ pos.y * g_game.img_map->size_line
				+ pos.x * g_game.img_map->bpp));
			if ((color & 0xff0000) != 0)
				*((int*)(g_game.img_view->data
					+ pos.y * g_game.img_view->size_line
					+ pos.x * g_game.img_view->bpp)) = color;
			pos.x++;
		}
		pos.y++;
	}
}
