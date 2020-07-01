/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 13:17:08 by fyusuf-a          #+#    #+#             */
/*   Updated: 2020/07/01 20:04:29 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static inline void
	draw_pixel(t_image *img, int32_t color, t_2d_int pos)
{
	*((int32_t*)(img->data + pos.y * img->size_line +
				pos.x * img->bpp)) = color;
}

void
	draw_rectangle(t_image *img, int32_t color, t_2d_int origin,
							t_2d_int dim)
{
	int			i;
	int			j;
	t_2d_int	pos;

	i = ft_min(origin.y, origin.y + dim.y);
	while (i <= ft_max(origin.y, origin.y + dim.y))
	{
		j = ft_min(origin.x, origin.x + dim.x);
		while (j <= ft_max(origin.x, origin.x + dim.x))
		{
			pos.y = i;
			pos.x = j;
			draw_pixel(img, color, pos);
			j++;
		}
		i++;
	}
}

void
	draw_rectangle_from_center(t_image *img, int32_t color,
			t_2d_int center, t_2d_int dim)
{
	center.x -= dim.x / 2;
	center.y -= dim.y / 2;
	draw_rectangle(img, color, center, dim);
}

void
	draw(t_player *old_player, t_player *new_player)
{
	draw_view(new_player);
	draw_minimap(old_player, new_player);
	if (mlx_put_image_to_window(g_game.conn.mlx_ptr, g_game.conn.win_ptr,
			g_game.img_view->ptr, 0, 0) < 0)
		error("draw_view: mlx_put_image_to_window failed");
}
