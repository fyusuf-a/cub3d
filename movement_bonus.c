/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 23:56:52 by fyusuf-a          #+#    #+#             */
/*   Updated: 2020/07/02 10:27:38 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int
	far_from_wall(t_2d pos)
{
	t_2d new_pos;

	new_pos = pos;
	new_pos.x += SCREEN_DISTANCE;
	if (what_is(new_pos) == WALL)
		return (0);
	new_pos = pos;
	new_pos.x -= SCREEN_DISTANCE;
	if (what_is(new_pos) == WALL)
		return (0);
	new_pos = pos;
	new_pos.y += SCREEN_DISTANCE;
	if (what_is(new_pos) == WALL)
		return (0);
	new_pos = pos;
	new_pos.y -= SCREEN_DISTANCE;
	if (what_is(new_pos) == WALL)
		return (0);
	return (1);
}

int
	is_update_needed(const t_player *new_player)
{
	int			ret;
	t_2d		player_cell;
	t_object	current_object;

	ret = far_from_wall(new_player->pos);
	current_object = what_is(new_player->pos);
	if (current_object == OBJECT)
	{
		player_cell = what_cell(new_player->pos);
		ret = ret &&
			dist(new_player->pos, player_cell) >= 0.5 + SCREEN_DISTANCE;
	}
	return (ret);
}

t_player
	update_pos(t_player player)
{
	t_player	copy;

	copy = player;
	if (g_game.keyboard.w)
		copy.pos.x += STEP * cos(g_game.player.angle);
	if (g_game.keyboard.s)
		copy.pos.x -= STEP * cos(g_game.player.angle);
	if (g_game.keyboard.a)
		copy.pos.x += STEP * sin(g_game.player.angle);
	if (g_game.keyboard.d)
		copy.pos.x -= STEP * sin(g_game.player.angle);
	if (is_update_needed(&copy))
		player = copy;
	copy = player;
	if (g_game.keyboard.w)
		copy.pos.y += STEP * sin(g_game.player.angle);
	if (g_game.keyboard.s)
		copy.pos.y -= STEP * sin(g_game.player.angle);
	if (g_game.keyboard.a)
		copy.pos.y -= STEP * cos(g_game.player.angle);
	if (g_game.keyboard.d)
		copy.pos.y += STEP * cos(g_game.player.angle);
	if (is_update_needed(&copy))
		player = copy;
	return (player);
}
