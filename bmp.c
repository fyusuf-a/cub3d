/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/20 12:58:08 by fyusuf-a          #+#    #+#             */
/*   Updated: 2020/06/24 22:45:52 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	power(int exponent, int number)
{
	if (exponent == 0)
		return (1);
	return (number * power(exponent - 1, number));
}

static void	print_number_binary(int fd, int number, int byte_number)
{
	char	*res;
	int		i;
	int		j;

	if (!(res = malloc(byte_number)))
		error("print_number_binary: malloc failed");
	i = byte_number - 1;
	while (i >= 0)
	{
		res[i] = 0;
		j = 0;
		while (j < 8)
		{
			res[i] += power(2, 7 - j) * (number % 2);
			number /= 2;
			j++;
		}
		i--;
	}
	i = 0;
	while (i < byte_number)
		dprintf(fd, "%c", res[i++]);
	free(res);
}

void	print_bmp(const t_image *image, const char *path)
{
	int fd;
	int i;
	int size;

	if ((fd = open(path, O_CREAT | O_WRONLY, 0664)) < 0)
		error("print_bmp: opening write-only file \"%s\" failed", path);
	/*printf("%o\n", 3 * g_game.img_view->res.x * g_game.img_view->res.y);*/
	/*dprintf(fd, "%04o\n", 3 * g_game.img_view->res.x * g_game.img_view->res.y);*/
	size = 3 * g_game.img_view->res.x * g_game.img_view->res.y;
	print_number_binary(fd, 45, 4);
	if (size > 4294967295)
		error("print_size: bmp size exceeds 4 bytes");
	/*ft_dprintf(fd, "BM%d\x12\x12", 14);*/
	/*dprintf(fd, "hello");*/
	/*ft_printf(fd, "%", 14);*/
	close(fd);
}
