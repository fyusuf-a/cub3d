/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 15:00:18 by fyusuf-a          #+#    #+#             */
/*   Updated: 2020/05/18 16:15:38 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	copy_from_buffer(t_image *img)
{
	int i;

	i = 0;
	while (i < img->res.x * img->res.y)
	{
		img->data[i * img->bpp] = img->buffer[i * img->bpp];
		img->data[i * img->bpp + 1] = img->buffer[i * img->bpp + 1];
		img->data[i * img->bpp + 2] = img->buffer[i * img->bpp + 2];
		i++;
	}
}
