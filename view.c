/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 17:42:09 by fyusuf-a          #+#    #+#             */
/*   Updated: 2020/06/06 18:09:44 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	convert(t_image *img, double height)
{
	return (height / SCREEN_WIDTH * img->res.y);
}

void		draw_wall_texture(const t_list *ray, int perceived_height, int limit_above,
										t_2d_int *pos_view)
{
	t_2d_int	pos_texture;
	double		dist_to_corner;
	t_2d		impact;
	t_image		*texture;

	impact = ((t_contact*)ray->content)->impact;
	if (((t_contact*)ray->content)->cardinal_point == SOUTH)
	{
		texture = g_game.config->texture_no;
		dist_to_corner = impact.x - ((int)(impact.x + 0.5) - 0.5);
	}
	else if (((t_contact*)ray->content)->cardinal_point == NORTH)
	{
		texture = g_game.config->texture_so;
		dist_to_corner = ((int)(impact.x + 1.5) - 0.5) - impact.x;
	}
	else if (((t_contact*)ray->content)->cardinal_point == WEST)
	{
		texture = g_game.config->texture_ea;
		dist_to_corner = impact.y - ((int)(impact.y + 0.5) - 0.5);
	}
	else
	{
		texture = g_game.config->texture_we;
		dist_to_corner = ((int)(impact.y + 1.5) - 0.5) - impact.y;
	}
	pos_texture.x = (double)texture->res.x * dist_to_corner;
	while (pos_view->y < limit_above + perceived_height)
	{
		pos_texture.y = (double)(pos_view->y - limit_above) /
					(double)perceived_height * texture->res.y;
		pos_texture.y = pos_texture.y >= texture->res.y ?
							texture->res.y - 1 : pos_texture.y;
		draw_pixel(g_game.img_view,
						color_from_image(texture, pos_texture), pos_view);
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
	int			limit_above;
	double		perceived_height;
	double		dist_to_sprite;
	double		temp_angle;
	t_2d_int	pos_texture;
	t_2d		center;
	t_contact	current_contact;

	if (ray != NULL)
	{
		current_contact = *((t_contact*)ray->content);
		if (temp_player->pos.x == current_contact.impact.x && temp_player->pos.y == current_contact.impact.y)
			center = what_cell(temp_player->pos);
		else
			center = what_cell(displaced((t_contact*)ray->content));
		temp_angle = atan((center.y - temp_player->pos.y) / (center.x - temp_player->pos.x));
		temp_angle -= temp_player->angle;
		dist_to_sprite = dist(temp_player->pos, center);
		if (dist_to_sprite * abs_val(tan(temp_angle)) > 0.5)
			perceived_height = 0;
		else
		{
			dist_to_sprite /= cos(temp_angle);
			dist_to_sprite *= cos(new_player->angle - temp_player->angle);
			perceived_height = SCREEN_DISTANCE * WALL_HEIGHT / abs_val(dist_to_sprite);
		}
		limit_above = g_game.img_view->res.y - convert(g_game.img_view,
									(SCREEN_WIDTH + perceived_height) / 2);
		/*cell = what_cell(*/
		/*if (((t_contact*)ray->content)->cardinal_point == SOUTH)*/
		/*dist_to_corner = impact.x - ((int)(impact.x + 0.5) - 0.5);*/
		/*else if (((t_contact*)ray->content)->cardinal_point == NORTH)*/
			/*dist_to_corner = ((int)(impact.x + 1.5) - 0.5) - impact.x;*/
		/*else if (((t_contact*)ray->content)->cardinal_point == WEST)*/
			/*dist_to_corner = impact.y - ((int)(impact.y + 0.5) - 0.5);*/
		/*else*/
			/*dist_to_corner = ((int)(impact.y + 1.5) - 0.5) - impact.y;*/
		/*pos_texture.x = (double)g_game.config->texture_sprite->res.x * dist_to_corner;*/
		pos_texture.x = 0;
		pos_view->y = limit_above;
		while (pos_view->y < limit_above + convert(g_game.img_view, perceived_height))
		{
			pos_texture.y = (double)(pos_view->y - limit_above) /
					(double)perceived_height * g_game.config->texture_sprite->res.y;
			pos_texture.y = pos_texture.y >= g_game.config->texture_sprite->res.y ?
							g_game.config->texture_sprite->res.y - 1 : pos_texture.y;
			draw_pixel(g_game.img_view,
				g_white, pos_view);
				/*color_from_image(g_game.config->texture_sprite, pos_texture), pos_view);*/
			pos_view->y++;
		}
	}
}

static void	draw_wall_column(t_2d_int *pos_view, const t_player *temp_player,
								const t_player *new_player, const t_list *ray)
{
	int			limit_above;
	double		perceived_height;
	t_2d		impact;
	double		dist_to_wall;

	impact = ((t_contact*)ray->content)->impact;
	dist_to_wall = dist(temp_player->pos, impact);
	dist_to_wall *= cos(new_player->angle - temp_player->angle);
	perceived_height = SCREEN_DISTANCE * WALL_HEIGHT / dist_to_wall;
	limit_above = g_game.img_view->res.y - convert(g_game.img_view,
								(SCREEN_WIDTH + perceived_height) / 2);
	pos_view->y = 0;
	while (pos_view->y < limit_above && pos_view->y < g_game.img_view->res.y)
	{
		draw_pixel(g_game.img_view, g_game.config->ceiling, pos_view);
		pos_view->y++;
	}
	draw_wall_texture(ray, convert(g_game.img_view, perceived_height),
													limit_above, pos_view);
	while (pos_view->y < g_game.img_view->res.y)
	{
		draw_pixel(g_game.img_view, g_game.config->floor, pos_view);
		pos_view->y++;
	}
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
	mlx_put_image_to_window(g_game.conn->mlx_ptr, g_game.conn->win_ptr,
			g_game.img_view->ptr, 0, 0);
}
