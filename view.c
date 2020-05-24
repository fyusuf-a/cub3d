/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 17:42:09 by fyusuf-a          #+#    #+#             */
/*   Updated: 2020/05/24 21:07:02 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	convert(t_image *img, double height)
{
	return (height / SCREEN_WIDTH * img->res.y);
}

static void	draw_column(t_game *game, int i, double dist)
{
	int			limit_below;
	int			limit_above;
	double		perceived_height;
	t_2d_int	pos;

	pos.x = i;
	pos.y = 0;
	perceived_height = SCREEN_DISTANCE * WALL_HEIGHT / dist;
	limit_below = convert(game->img_view,
								(SCREEN_WIDTH - perceived_height) / 2);
	limit_above = convert(game->img_view,
								(SCREEN_WIDTH + perceived_height) / 2);
	while (pos.y < game->img_view->res.y)
	{
		if (pos.y < limit_below)
			draw_pixel(game->img_view, game->config->floor, pos);
		else if (pos.y > limit_above)
			draw_pixel(game->img_view, game->config->ceiling, pos);
		else
			draw_pixel(game->img_view, g_black, pos);
		pos.y++;
	}
}

void		draw_view(t_game *game, t_player *new_player)
{
	int			i;
	double		angle_increment;
	double		distance;
	t_player	temp_player;
	t_contact	contact;

	temp_player = *new_player;
	temp_player.angle = new_player->angle - (M_PI / 4) / 2;
	angle_increment = (M_PI / 4) / ((double)game->config->resolution.x);
	i = 0;
	while (i < game->img_view->res.x)
	{
		contact = contact_with_wall(game, &temp_player);
		distance = dist(temp_player.pos, contact.impact);
		distance *= cos(new_player->angle - temp_player.angle);
		draw_column(game, i, distance);
		temp_player.angle += angle_increment;
		i++;
	}
	mlx_put_image_to_window(game->conn->mlx_ptr, game->conn->win_ptr,
			game->img_view->ptr, 0, 0);
}
