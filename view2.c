/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 17:45:53 by fyusuf-a          #+#    #+#             */
/*   Updated: 2020/07/22 10:34:14 by fyusuf-a         ###   ########.fr       */
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
	draw_vertically_until(int limit, int32_t color)
{
	while (g_game.pencil.y < limit)
	{
		draw_pixel(g_game.img_view, color, g_game.pencil);
		g_game.pencil.y++;
	}
}

static void
	find_dist_to_sprite_and_temp_angle(double *dist_to_sprite,
		double *temp_angle, const t_player *temp_player, const t_list *ray)
{
	t_contact	*contact;
	t_2d		center;

	contact = (t_contact*)ray->content;
	center = what_cell(
		pos_equals(temp_player->pos, contact->impact) ?
		temp_player->pos : displaced(contact));
	*dist_to_sprite = dist(temp_player->pos, center);
	*temp_angle = temp_player->angle - 
		atan((center.y - temp_player->pos.y) / (center.x - temp_player->pos.x));
}

void
	draw_sprites_column(const t_player *temp_player,
								const t_player *new_player, const t_list *ray)
{
	double		perceived_height;
	double		dist_to_sprite;
	double		dist_contact_to_sprite;
	double		temp_angle;
	int			limit_above;

	if (ray != NULL)
	{
		find_dist_to_sprite_and_temp_angle(&dist_to_sprite, &temp_angle,
												temp_player, ray);
		dist_contact_to_sprite = dist_to_sprite * tan(temp_angle);
		if (abs_val(dist_contact_to_sprite) <= 0.5)
		{
			dist_to_sprite /= cos(temp_angle);
			perceived_height = SCREEN_DISTANCE * WALL_HEIGHT / abs_val(
				dist_to_sprite * cos(new_player->angle - temp_player->angle));
			limit_above = g_game.img_view->res.y - convert_height(
					g_game.img_view,
					(g_game.screen_height + perceived_height) / 2);
			g_game.drawn_texture = g_game.config.texture_sprite;
			draw_texture(perceived_height, 0.5 + dist_contact_to_sprite,
							limit_above, 1);
		}
		draw_sprites_column(temp_player, new_player, ray->next);
	}
}
