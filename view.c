/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 17:42:09 by fyusuf-a          #+#    #+#             */
/*   Updated: 2020/05/29 18:00:24 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	convert(t_image *img, double height)
{
	return (height / SCREEN_WIDTH * img->res.y);
}

void		draw_texture(t_ray *ray, int perceived_height, int limit_below, int limit_above, t_2d_int *pos_view)
{
	t_image		*texture;
	t_2d_int	pos_texture;
	double		dist;
	t_2d		impact;

	impact = *((t_2d*)ray->list->content);
	if (ray->cardinal_point == NORTH)
	{
		texture = g_game.config->texture_no;
		dist = impact.x - ((int)(impact.x + 0.5) - 0.5);
	}
	else if (ray->cardinal_point == SOUTH)
	{
		texture = g_game.config->texture_so;
		dist = ((int)(impact.x + 1.5) - 0.5) - impact.x;
	}
	else if (ray->cardinal_point == EAST)
	{
		texture = g_game.config->texture_ea;
		dist = impact.y - ((int)(impact.y + 0.5) - 0.5);
	}
	else
	{
		texture = g_game.config->texture_we;
		dist = ((int)(impact.y + 1.5) - 0.5) - impact.y;
	}
	pos_texture.x = (double)texture->res.x * dist;
	while (pos_view->y < limit_below)
	{
		pos_texture.y = (double)(pos_view->y - limit_above) /
								(double)perceived_height * texture->res.y;
		pos_texture.y = pos_texture.y >= texture->res.y ?
							texture->res.y - 1 : pos_texture.y;
		draw_pixel(g_game.img_view, color_from_image(texture, pos_texture),
						pos_view);
		pos_view->y++;
	}
}

static void	draw_column(t_2d_int *pos_view, double dist, t_ray *ray)
{
	int			limit_below;
	int			limit_above;
	double		perceived_height;
	int			perceived_height_int;

	pos_view->y = 0;
	perceived_height = SCREEN_DISTANCE * WALL_HEIGHT / dist;
	limit_above = g_game.img_view->res.y - convert(g_game.img_view,
								(SCREEN_WIDTH + perceived_height) / 2);
	limit_below = g_game.img_view->res.y - convert(g_game.img_view,
								(SCREEN_WIDTH - perceived_height) / 2);
	perceived_height_int = convert(g_game.img_view, perceived_height);
	while (pos_view->y < limit_above && pos_view->y < g_game.img_view->res.y)
	{
		draw_pixel(g_game.img_view, g_game.config->ceiling, pos_view);
		pos_view->y++;
	}
	draw_texture(ray, perceived_height_int, limit_below, limit_above, pos_view);
	while (pos_view->y < g_game.img_view->res.y)
	{
		draw_pixel(g_game.img_view, g_game.config->floor, pos_view);
		pos_view->y++;
	}
}

void		draw_view(t_player *new_player)
{
	double		angle_increment;
	double		distance;
	t_player	temp_player;
	t_2d_int	pos_in_view;
	t_2d		impact;

	temp_player = *new_player;
	temp_player.angle = new_player->angle - (M_PI / 4) / 2;
	angle_increment = (M_PI / 4) / ((double)g_game.config->resolution.x);
	pos_in_view.x = 0;
	while (pos_in_view.x < g_game.img_view->res.x)
	{
		g_game.ray = contact_with_wall(&temp_player);
		impact = *((t_2d *)g_game.ray->list->content);
		distance = dist(temp_player.pos, impact);
		distance *= cos(new_player->angle - temp_player.angle);
		draw_column(&pos_in_view, distance, g_game.ray);
		temp_player.angle += angle_increment;
		pos_in_view.x++;
	}
	/*copy_from_buffer(g_game.img_view);*/
	mlx_put_image_to_window(g_game.conn->mlx_ptr, g_game.conn->win_ptr,
			g_game.img_view->ptr, 0, 0);
}
