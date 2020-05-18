/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 15:40:26 by fyusuf-a          #+#    #+#             */
/*   Updated: 2020/05/18 15:55:11 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_not_vertical_line(t_image *img, t_line_params *params,
										t_2d_int point1, t_2d_int point2)
{
	t_2d_int	temp;
	t_2d_int	temp_center;
	t_2d_int	temp_dim;
	double		m;

	m = ((double)(point1.y - point2.y)) / ((double)(point1.x - point2.x));
	if (point2.x < point1.x)
	{
		temp = point1;
		point1 = point2;
		point2 = temp;
	}
	temp_center.x = point1.x;
	temp_dim.x = 1;
	temp_dim.y = params->thickness / 2;
	while (temp_center.x <= point2.x)
	{
		temp_center.y = (m * (double)(temp_center.x - point1.x)) + point1.y;
		draw_rectangle_from_center(img, params->color, temp_center, temp_dim);
		temp_center.x++;
	}
}

void		draw_line(t_image *img, t_line_params *params, t_2d_int point1,
						t_2d_int point2)
{
	t_2d_int	temp_center;
	t_2d_int	temp_dim;

	if (point1.x == point2.x)
	{
		temp_center.x = (point1.x + point2.x) / 2;
		temp_center.y = (point1.y + point2.y) / 2;
		temp_dim.x = params->thickness / 2;
		temp_dim.y = ft_abs(point1.y - point2.y);
		draw_rectangle_from_center(img, params->color, temp_center, temp_dim);
		return ;
	}
	draw_not_vertical_line(img, params, point1, point2);
}
