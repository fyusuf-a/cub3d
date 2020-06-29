/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 10:23:26 by fyusuf-a          #+#    #+#             */
/*   Updated: 2020/06/29 12:17:48 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int
	key_pressed(int key)
{
	if (key == W)
		g_game.keyboard.w = 1;
	if (key == S)
		g_game.keyboard.s = 1;
	if (key == A)
		g_game.keyboard.a = 1;
	if (key == D)
		g_game.keyboard.d = 1;
	if (key == LEFT)
		g_game.keyboard.left = 1;
	if (key == RIGHT)
		g_game.keyboard.right = 1;
	if (key == ESCAPE)
		g_game.keyboard.escape = 1;
	return (EXIT_SUCCESS);
}

int
	key_released(int key)
{
	if (key == W)
		g_game.keyboard.w = 0;
	if (key == S)
		g_game.keyboard.s = 0;
	if (key == A)
		g_game.keyboard.a = 0;
	if (key == D)
		g_game.keyboard.d = 0;
	if (key == LEFT)
		g_game.keyboard.left = 0;
	if (key == RIGHT)
		g_game.keyboard.right = 0;
	if (key == ESCAPE)
		g_game.keyboard.escape = 0;
	return (EXIT_SUCCESS);
}
