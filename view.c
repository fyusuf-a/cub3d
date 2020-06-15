/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 17:42:09 by fyusuf-a          #+#    #+#             */
/*   Updated: 2020/06/15 17:55:57 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int
	convert_height(t_image *img, double height)
{
	return (height / g_game.screen_height * img->res.y);
}

void
	draw_texture(double perceived_height, double dist,
								int limit_above, int ignore_black)
{
	t_2d_int	pos_texture;
	double		perceived_height_int;
	t_color		color;

	g_game.pencil.y = limit_above;
	perceived_height_int = convert_height(g_game.img_view, perceived_height);
	pos_texture.x = (double)g_game.drawn_texture->res.x * dist;
	while (g_game.pencil.y < limit_above + perceived_height_int)
	{
		pos_texture.y = (double)(g_game.pencil.y - limit_above) /
					(double)perceived_height_int * g_game.drawn_texture->res.y;
		pos_texture.y = pos_texture.y >= g_game.drawn_texture->res.y ?
							g_game.drawn_texture->res.y - 1 : pos_texture.y;
		color = color_from_image(g_game.drawn_texture, pos_texture);
		if (ignore_black && color.r == 0 && color.g == 0 && color.b == 0)
		{
			g_game.pencil.y++;
			continue ;
		}
		draw_pixel(g_game.img_view, color, &g_game.pencil);
		g_game.pencil.y++;
	}
}

static void
	find_texture_and_dist_to_corner(double *dist_to_corner,
									const t_contact *contact)
{
	if (contact->cardinal_point == SOUTH)
	{
		g_game.drawn_texture = g_game.config->texture_no;
		*dist_to_corner = contact->impact.x
							- ((int)(contact->impact.x + 0.5) - 0.5);
	}
	else if (contact->cardinal_point == NORTH)
	{
		g_game.drawn_texture = g_game.config->texture_so;
		*dist_to_corner = ((int)(contact->impact.x + 1.5) - 0.5)
							- contact->impact.x;
	}
	else if (contact->cardinal_point == WEST)
	{
		g_game.drawn_texture = g_game.config->texture_ea;
		*dist_to_corner = contact->impact.y
							- ((int)(contact->impact.y + 0.5) - 0.5);
	}
	else
	{
		g_game.drawn_texture = g_game.config->texture_we;
		*dist_to_corner = ((int)(contact->impact.y + 1.5) - 0.5)
							- contact->impact.y;
	}
}

static void
	draw_wall_column(const t_player *temp_player,
					const t_player *new_player, const t_list *ray)
{
	int			limit_above;
	double		perceived_height;
	double		dist_to_wall;
	double		dist_to_corner;

	dist_to_wall = dist(temp_player->pos, ((t_contact*)ray->content)->impact);
	dist_to_wall *= cos(new_player->angle - temp_player->angle);
	perceived_height = SCREEN_DISTANCE * WALL_HEIGHT / dist_to_wall;
	find_texture_and_dist_to_corner(&dist_to_corner, ray->content);
	limit_above = g_game.img_view->res.y - convert_height(g_game.img_view,
								(g_game.screen_height + perceived_height) / 2);
	g_game.pencil.y = 0;
	while (g_game.pencil.y < limit_above &&
				g_game.pencil.y < g_game.img_view->res.y)
	{
		draw_pixel(g_game.img_view, g_game.config->ceiling, &g_game.pencil);
		g_game.pencil.y++;
	}
	draw_texture(perceived_height, dist_to_corner, limit_above, 0);
	while (g_game.pencil.y < g_game.img_view->res.y)
	{
		draw_pixel(g_game.img_view, g_game.config->floor, &g_game.pencil);
		g_game.pencil.y++;
	}
}

void
	draw_view(t_player *new_player)
{
	double		angle_increment;
	t_player	temp_player;

	temp_player = *new_player;
	temp_player.angle = new_player->angle - (M_PI / 4) / 2;
	angle_increment = (M_PI / 4) / ((double)g_game.config->resolution.x);
	g_game.pencil.x = 0;
	while (g_game.pencil.x < g_game.img_view->res.x)
	{
		g_game.ray = contact_with_wall(&temp_player, &g_iter);
		draw_wall_column(&temp_player, new_player,
								g_game.ray);
		draw_sprites_column(&temp_player, new_player, g_game.ray->next);
		temp_player.angle += angle_increment;
		g_game.pencil.x++;
	}
	/*copy_from_buffer(g_game.img_view);*/
	if (mlx_put_image_to_window(g_game.conn->mlx_ptr, g_game.conn->win_ptr,
			g_game.img_view->ptr, 0, 0) < 0)
		error("draw_view: mlx_put_image_to_window failed");
}
