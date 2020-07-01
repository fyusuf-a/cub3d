/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 17:15:25 by fyusuf-a          #+#    #+#             */
/*   Updated: 2020/07/01 11:13:11 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void
	del(void *content)
{
	free((t_contact*)content);
}

void
	free_ray(t_list *ray)
{
	ft_lstclear(&ray, del);
	free(ray);
}

int
	free_and_exit_game(void)
{
	free_game();
	exit(EXIT_SUCCESS);
}
