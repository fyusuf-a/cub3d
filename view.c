/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 17:42:09 by fyusuf-a          #+#    #+#             */
/*   Updated: 2020/05/27 23:07:03 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	convert(t_image *img, double height)
{
	return (height / SCREEN_WIDTH * img->res.y);
}

void		draw_texture(t_game *game, t_contact *contact, int perceived_height, int limit_below, int limit_above, t_2d_int *pos_view)
{
	t_image		*texture;
	t_2d_int	pos_texture;
	double		dist;

	if (contact->cardinal_point == NORTH)
	{
		texture = game->config->texture_no;
		dist = contact->impact.x - ((int)(contact->impact.x + 0.5) - 0.5);
	}
	else if (contact->cardinal_point == SOUTH)
	{
		texture = game->config->texture_so;
		dist = ((int)(contact->impact.x + 1.5) - 0.5) - contact->impact.x;
	}
	else if (contact->cardinal_point == EAST)
	{
		texture = game->config->texture_ea;
		dist = contact->impact.y - ((int)(contact->impact.y + 0.5) - 0.5);
	}
	else
	{
		texture = game->config->texture_we;
		dist = ((int)(contact->impact.y + 1.5) - 0.5) - contact->impact.y;
	}
	pos_texture.x = (double)texture->res.x * dist;
	while (pos_view->y < limit_below)
	{
		pos_texture.y = (double)(pos_view->y - limit_above) /
								(double)perceived_height * texture->res.y;
		pos_texture.y >= texture->res.y ? pos_texture.y = texture->res.y - 1: 0;
		draw_pixel(game->img_view, color_from_image(texture, pos_texture),
						pos_view);
		pos_view->y++;
	}
}

static void	draw_column(t_game *game, t_2d_int *pos_view, double dist,
							t_contact *contact)
{
	int			limit_below;
	int			limit_above;
	double		perceived_height;
	int			perceived_height_int;

	pos_view->y = 0;
	perceived_height = SCREEN_DISTANCE * WALL_HEIGHT / dist;
	limit_above = game->img_view->res.y - convert(game->img_view,
								(SCREEN_WIDTH + perceived_height) / 2);
	limit_below = game->img_view->res.y - convert(game->img_view,
								(SCREEN_WIDTH - perceived_height) / 2);
	perceived_height_int = convert(game->img_view, perceived_height);
	while (pos_view->y < limit_above && pos_view->y < game->img_view->res.y)
	{
		draw_pixel(game->img_view, game->config->ceiling, pos_view);
		pos_view->y++;
	}
	draw_texture(game, contact, perceived_height_int, limit_below, limit_above,
								pos_view);
	while (pos_view->y < game->img_view->res.y)
	{
		draw_pixel(game->img_view, game->config->floor, pos_view);
		pos_view->y++;
	}
}

void		draw_view(t_game *game, t_player *new_player)
{
	double		angle_increment;
	double		distance;
	t_player	temp_player;
	t_contact	contact;
	t_2d_int	pos_in_view;

	temp_player = *new_player;
	temp_player.angle = new_player->angle - (M_PI / 4) / 2;
	angle_increment = (M_PI / 4) / ((double)game->config->resolution.x);
	pos_in_view.x = 0;
	while (pos_in_view.x < game->img_view->res.x)
	{
		contact = contact_with_wall(game, &temp_player);
		distance = dist(temp_player.pos, contact.impact);
		distance *= cos(new_player->angle - temp_player.angle);
		draw_column(game, &pos_in_view, distance, &contact);
		temp_player.angle += angle_increment;
		pos_in_view.x++;
	}
	/*copy_from_buffer(game->img_view);*/
	mlx_put_image_to_window(game->conn->mlx_ptr, game->conn->win_ptr,
			game->img_view->ptr, 0, 0);
}
