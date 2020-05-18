/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 13:17:08 by fyusuf-a          #+#    #+#             */
/*   Updated: 2020/05/18 16:11:08 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_pixel(t_image *img, t_color color, t_2d_int pos)
{
	char	*array;

	array = img->buffered ? img->buffer : img->data;
	if (pos.x >= 0 && pos.x < img->res.x && pos.y >= 0 && pos.y < img->res.y)
	{
		array[pos.y * img->res.x * img->bpp + pos.x * img->bpp] = color.r;
		array[pos.y * img->res.x * img->bpp + pos.x * img->bpp + 1] = color.g;
		array[pos.y * img->res.x * img->bpp + pos.x * img->bpp + 2] = color.b;
	}
}

void	draw_rectangle(t_image *img, t_color color, t_2d_int origin,
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

void	draw_rectangle_from_center(t_image *img, t_color color, t_2d_int center,
		t_2d_int dim)
{
	center.x -= dim.x / 2;
	center.y -= dim.y / 2;
	draw_rectangle(img, color, center, dim);
}

void	draw(t_game *game, t_player *old_player, t_player *new_player)
{
	draw_minimap(game, old_player, new_player);
}
