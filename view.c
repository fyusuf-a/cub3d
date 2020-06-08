/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 17:42:09 by fyusuf-a          #+#    #+#             */
/*   Updated: 2020/06/08 19:16:43 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	convert(t_image *img, double height)
{
	return (height / SCREEN_WIDTH * img->res.y);
}

void		draw_texture(double perceived_height, t_2d_int *pos_view, double dist, double limit_above, int ignore_black)
{
	t_2d_int	pos_texture;
	/*int			limit_above;*/
	double		perceived_height_int;
	t_color		color;

	perceived_height_int = convert(g_game.img_view, perceived_height);
	/*limit_above = g_game.img_view->res.y - convert(g_game.img_view,*/
								/*(SCREEN_WIDTH + perceived_height) / 2);*/
	pos_texture.x = (double)g_game.drawn_texture->res.x * dist;
	while (pos_view->y < limit_above + perceived_height_int)
	{
		pos_texture.y = (double)(pos_view->y - limit_above) /
					(double)perceived_height_int * g_game.drawn_texture->res.y;
		pos_texture.y = pos_texture.y >= g_game.drawn_texture->res.y ?
							g_game.drawn_texture->res.y - 1 : pos_texture.y;
		color = color_from_image(g_game.drawn_texture, pos_texture);
		if (color.r == 0 && color.g == 0 && color.b == 0)
		{
			pos_view->y++;
			continue ;
		}
		draw_pixel(g_game.img_view, color, pos_view);
		pos_view->y++;
	}
}

static double	abs_val(double x)
{
	return (x >= 0 ? x : -x);
}

static void	draw_sprites_column(t_2d_int *pos_view, const t_player *temp_player,
								const t_player *new_player, const t_list *ray)
{
	double		perceived_height;
	double		dist_to_sprite;
	double		dist_contact_to_sprite;
	double		temp_angle;
	t_2d		center;
	t_contact	*contact;	
	int			limit_above;

	if (ray != NULL)
	{
		contact = (t_contact*)ray->content;
		center = what_cell( temp_player->pos.x == contact->impact.x && temp_player->pos.y == contact->impact.y ?
								temp_player->pos : displaced(contact));
		dist_to_sprite = dist(temp_player->pos, center);
		temp_angle = atan((center.y - temp_player->pos.y) / (center.x - temp_player->pos.x));
		temp_angle -= temp_player->angle;
		dist_contact_to_sprite = dist_to_sprite * tan(temp_angle);
		if (abs_val(dist_contact_to_sprite) > 0.5)
			return ;
		dist_to_sprite /= cos(temp_angle);
		/*dist_to_sprite *= cos(new_player->angle - temp_player->angle);*/
		perceived_height = SCREEN_DISTANCE * WALL_HEIGHT /
			abs_val(dist_to_sprite * cos(new_player->angle - temp_player->angle));
		limit_above = g_game.img_view->res.y - convert(g_game.img_view,
									(SCREEN_WIDTH + perceived_height) / 2);
		pos_view->y = limit_above;
		g_game.drawn_texture = g_game.config->texture_sprite;
		draw_texture(perceived_height, pos_view, 0.5 + dist_contact_to_sprite, limit_above, 1);
	}
}

static void	draw_wall_column(t_2d_int *pos_view, const t_player *temp_player,
								const t_player *new_player, const t_list *ray)
{
	t_contact	*contact;
	int			limit_above;
	double		perceived_height;
	double		dist_to_wall;
	double		dist_to_corner;

	contact = (t_contact*)ray->content;
	dist_to_wall = dist(temp_player->pos, contact->impact);
	dist_to_wall *= cos(new_player->angle - temp_player->angle);
	perceived_height = SCREEN_DISTANCE * WALL_HEIGHT / dist_to_wall;
	if (contact->cardinal_point == SOUTH)
	{
		g_game.drawn_texture = g_game.config->texture_no;
		dist_to_corner = contact->impact.x - ((int)(contact->impact.x + 0.5) - 0.5);
	}
	else if (contact->cardinal_point == NORTH)
	{
		g_game.drawn_texture = g_game.config->texture_so;
		dist_to_corner = ((int)(contact->impact.x + 1.5) - 0.5) - contact->impact.x;
	}
	else if (contact->cardinal_point == WEST)
	{
		g_game.drawn_texture = g_game.config->texture_ea;
		dist_to_corner = contact->impact.y - ((int)(contact->impact.y + 0.5) - 0.5);
	}
	else
	{
		g_game.drawn_texture = g_game.config->texture_we;
		dist_to_corner = ((int)(contact->impact.y + 1.5) - 0.5) - contact->impact.y;
	}
	limit_above = g_game.img_view->res.y - convert(g_game.img_view,
								(SCREEN_WIDTH + perceived_height) / 2);
	pos_view->y = 0;
	while (pos_view->y < limit_above && pos_view->y < g_game.img_view->res.y)
	{
		draw_pixel(g_game.img_view, g_game.config->ceiling, pos_view);
		pos_view->y++;
	}
	draw_texture(perceived_height, pos_view, dist_to_corner, limit_above, 0);
	/*draw_texture(ray, convert(g_game.img_view, perceived_height),*/
													/*limit_above, pos_view);*/
	while (pos_view->y < g_game.img_view->res.y)
	{
		draw_pixel(g_game.img_view, g_game.config->floor, pos_view);
		pos_view->y++;
	}
}

void put_whatever(t_image *img)
{
	t_2d_int pos;

	for (pos.x = 0; pos.x < img->res.x; pos.x++)
		for (pos.y = 0;pos.y < img->res.y; pos.y++)
			draw_pixel(img, g_black, &pos);
}

void		draw_view(t_player *new_player)
{
	double		angle_increment;
	t_player	temp_player;
	t_2d_int	pos_in_view;

	temp_player = *new_player;
	temp_player.angle = new_player->angle - (M_PI / 4) / 2;
	angle_increment = (M_PI / 4) / ((double)g_game.config->resolution.x);
	pos_in_view.x = 0;
	while (pos_in_view.x < g_game.img_view->res.x)
	{
		g_game.ray = contact_with_wall(&temp_player, &g_iter);
		draw_wall_column(&pos_in_view, &temp_player, new_player,
								g_game.ray);
		draw_sprites_column(&pos_in_view, &temp_player, new_player,
								g_game.ray->next);
		temp_player.angle += angle_increment;
		pos_in_view.x++;
	}
	/*copy_from_buffer(g_game.img_view);*/
	/*put_whatever(g_game.img_view);*/
	mlx_put_image_to_window(g_game.conn->mlx_ptr, g_game.conn->win_ptr,
			g_game.img_view->ptr, 0, 0);
	/*if(!(mlx_put_image_to_window(g_game.conn->mlx_ptr, g_game.conn->win_ptr,*/
			/*g_game.img_view->ptr, 0, 0)))*/
			/*error("oups");*/
}
