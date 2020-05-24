/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 17:42:09 by fyusuf-a          #+#    #+#             */
/*   Updated: 2020/05/24 23:42:41 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	convert(t_image *img, double height)
{
	return (height / SCREEN_WIDTH * img->res.y);
}

t_color		find_pixel_color(t_game *game, t_contact *contact, int height, int total_height)
{
	t_image		*image;
	t_2d_int	pos_in_texture;
	double		dist;

	if (contact->cardinal_point == NORTH)
	{
		image = game->config->texture_no;
		dist = contact->impact.x - ((int)(contact->impact.x + 0.5) - 0.5);
	}
	else if (contact->cardinal_point == SOUTH)
	{
		image = game->config->texture_so;
		dist = ((int)(contact->impact.x + 1.5) - 0.5) - contact->impact.x;
	}
	else if (contact->cardinal_point == EAST)
	{
		image = game->config->texture_ea;
		dist = contact->impact.y - ((int)(contact->impact.y + 0.5) - 0.5);
	}
	else
	{
		image = game->config->texture_we;
		dist = ((int)(contact->impact.y + 1.5) - 0.5) - contact->impact.y;
	}
	pos_in_texture.x = (double)image->res.x * dist;
	pos_in_texture.y = (double)height / (double)total_height * image->res.y;
	return (color_from_image(image, pos_in_texture));
}

static void	draw_column(t_game *game, int i, double dist, t_contact *contact)
{
	int			limit_below;
	int			limit_above;
	double		perceived_height;
	t_2d_int	pos;
	t_color		color;

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
		{
			color = find_pixel_color(game, contact,
					pos.y - limit_below, limit_above - limit_below);
			draw_pixel(game->img_view, color, pos);
		}
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
		draw_column(game, i, distance, &contact);
		temp_player.angle += angle_increment;
		i++;
	}
	mlx_put_image_to_window(game->conn->mlx_ptr, game->conn->win_ptr,
			game->img_view->ptr, 0, 0);
}
