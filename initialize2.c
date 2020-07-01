/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 21:15:04 by fyusuf-a          #+#    #+#             */
/*   Updated: 2020/06/29 23:26:15 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			initialize_mask(t_image *image)
{
	int	i;

	i = 0;
	if (image->bpp > 3)
	{
		while (i < image->res.x * image->res.y)
		{
			image->data[i * image->bpp + 3] = (char)255;
			i++;
		}
	}
}

static void		common_tasks(t_image *img)
{
	if (!(img->data = mlx_get_data_addr(img->ptr, &img->bpp,
											&img->size_line, &img->endian)))
		error("initialize_texture: mlx_get_data_addr failed");
	img->bpp /= 8;
	if (img->size_line != img->res.x * img->bpp)
	{
		error("initialize_game: unexpected size %d which is not equal to the "
				"horizontal resolution %d times the number of bytes per pixel "
				"%d in map image", img->size_line,
				img->res.x, img->bpp);
	}
}

t_image			*initialize_image(t_2d_int res)
{
	t_image	*ret;

	if (!(ret = malloc(sizeof(t_image))))
		error("initialize_image: could not allocate image");
	ret->res = res;
	ret->ptr = mlx_new_image(g_game.conn.mlx_ptr, res.x, res.y);
	common_tasks(ret);
	initialize_mask(ret);
	return (ret);
}

t_image			*initialize_texture(char *path)
{
	char	*needle;
	t_image	*ret;

	if (!(needle = ft_strrchr(path, '.')) || ft_strcmp(needle, ".xpm") != 0)
		error("%s: File extension should be .xpm", path);
	close_file(open_file(path));
	if (!(ret = malloc(sizeof(t_image))))
		error("initialize_texture: malloc failed");
	if (!(ret->ptr = mlx_xpm_file_to_image(g_game.conn.mlx_ptr, path,
											&(ret->res.x), &(ret->res.y))))
		error("initialize_texture: mlx_xpm_file_to_ret failed");
	common_tasks(ret);
	return (ret);
}
