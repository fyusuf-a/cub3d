/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/20 12:58:08 by fyusuf-a          #+#    #+#             */
/*   Updated: 2020/07/16 13:33:31 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static inline int32_t
	get_pixel(t_image *img, t_2d_int pos)
{
	return (*((int32_t*)(img->data + pos.y * img->size_line +
				pos.x * img->bpp)));
}

static void
	print_little_endian(int fd, int number, int byte_number)
{
	char	*res;
	int		i;

	if (!(res = malloc(byte_number)))
		error("print_number_binary: malloc failed");
	i = 0;
	while (i < byte_number)
		res[i++] = 0;
	i = 0;
	while (i < byte_number)
	{
		res[i++] = number % 256;
		number /= 256;
	}
	write(fd, res, byte_number);
	free(res);
}

static void
	bitmap_file_header(int fd)
{
	ft_dprintf(fd, "BM");
	print_little_endian(fd, 0, 4);
	ft_dprintf(fd, "%c%c%c%c", 0, 0, 0, 0);
	print_little_endian(fd, 14 + 40, 4);
}

static void
	bitmap_info_header(int fd)
{
	print_little_endian(fd, 40, 4);
	print_little_endian(fd, g_game.img_view->res.x, 4);
	print_little_endian(fd, g_game.img_view->res.y, 4);
	print_little_endian(fd, 1, 2);
	print_little_endian(fd, 3 * 8, 2);
	print_little_endian(fd, 0, 4);
	print_little_endian(fd, 0, 4);
	print_little_endian(fd, 0, 4);
	print_little_endian(fd, 0, 4);
	print_little_endian(fd, 0, 4);
	print_little_endian(fd, 0, 4);
}

void
	print_bmp(const char *path)
{
	int			fd;
	t_2d_int	pos;
	int			padding;

	if ((fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0664)) < 0)
		error("print_bmp: opening write-only file \"%s\" failed", path);
	padding = g_game.img_view->res.x % 4 ?
		4 - (g_game.img_view->res.x * 3 % 4) : 0;
	bitmap_file_header(fd);
	bitmap_info_header(fd);
	pos.y = g_game.img_view->res.y - 1;
	while (pos.y >= 0)
	{
		pos.x = 0;
		while (pos.x < g_game.img_view->res.x)
		{
			print_little_endian(fd, get_pixel(g_game.img_view, pos), 3);
			pos.x++;
		}
		print_little_endian(fd, 0, padding);
		pos.y--;
	}
	close(fd);
}
