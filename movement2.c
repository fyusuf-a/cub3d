/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 00:10:43 by fyusuf-a          #+#    #+#             */
/*   Updated: 2020/07/02 09:59:12 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void
	update_angle(t_player *new_player)
{
	if (g_game.keyboard.left)
		new_player->angle -= STEP;
	if (g_game.keyboard.right)
		new_player->angle += STEP;
}
