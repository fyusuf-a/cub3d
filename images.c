/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 15:00:18 by fyusuf-a          #+#    #+#             */
/*   Updated: 2020/05/24 23:53:01 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*void	copy_from_buffer(t_image *img)*/
/*{*/
	/*int i;*/

	/*i = 0;*/
	/*while (i < img->res.x * img->res.y)*/
	/*{*/
		/*img->data[i * img->bpp] = img->buffer[i * img->bpp];*/
		/*img->data[i * img->bpp + 1] = img->buffer[i * img->bpp + 1];*/
		/*img->data[i * img->bpp + 2] = img->buffer[i * img->bpp + 2];*/
		/*i++;*/
	/*}*/
/*}*/

t_color	color_from_image(t_image *img, t_2d_int pos)
{
	t_color	color;

	color.b = img->data[pos.y * img->res.x * img->bpp + pos.x * img->bpp];
	color.g = img->data[pos.y * img->res.x * img->bpp + pos.x * img->bpp + 1];
	color.r = img->data[pos.y * img->res.x * img->bpp + pos.x * img->bpp + 2];
	return (color);
}
