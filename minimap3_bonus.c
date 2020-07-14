/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap3_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 21:01:54 by fyusuf-a          #+#    #+#             */
/*   Updated: 2020/07/14 11:44:57 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void
	print_minimap(void)
{
	t_2d_int	pos;
	int32_t		color;

	pos.y = 0;
	while (pos.y < g_game.img_map->res.y)
	{
		pos.x = 0;
		while (pos.x < g_game.img_map->res.x)
		{
			color = *((int32_t*)(g_game.img_map->data
				+ pos.y * g_game.img_map->size_line
				+ pos.x * g_game.img_map->bpp));
			if ((color & 0xff0000) != 0)
				*((int32_t*)(g_game.img_view->data
					+ pos.y * g_game.img_view->size_line
					+ pos.x * g_game.img_view->bpp)) = color;
			pos.x++;
		}
		pos.y++;
	}
}

t_image
	*initialize_minimap(void)
{
	t_2d_int	res;
	t_image		*ret;

	if (g_game.map.dim.x < g_game.map.dim.y)
	{
		res.y = g_game.config.resolution.y;
		res.x = res.y / g_game.map.dim.y * g_game.map.dim.x;
	}
	else
	{
		res.x = g_game.config.resolution.x;
		res.y = res.x / g_game.map.dim.x * g_game.map.dim.y;
	}
	res.x /= 3;
	res.y /= 3;
	ret = initialize_image(res);
	g_game.map_color = ~g_game.config.ceiling;
	g_game.map_color |= 0xff000000;
	return (ret);
}
