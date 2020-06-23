/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/20 12:58:08 by fyusuf-a          #+#    #+#             */
/*   Updated: 2020/06/20 13:21:36 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_bmp(const t_image *image, const char *path)
{
	int fd;

	if ((fd = open(path, O_CREAT | S_IRUSR | S_IWUSR | O_WRONLY) < 0))
		error("print_bmp: opening write-only file \"%s\" failed", path);
	ft_dprintf(fd, "BM%d\x00\x00", 3);
	close(fd);
}
