/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 21:15:04 by fyusuf-a          #+#    #+#             */
/*   Updated: 2020/05/24 21:15:45 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		initialize_alpha(t_image *image, int alpha)
{
	int i;

	i = 0;
	if (image->bpp > 3)
		while (i < image->res.x * image->res.y)
		{
			image->data[i * image->bpp + 3] = alpha;
			i++;
		}
}

t_image			*initialize_image(t_game *game, t_2d_int res, int alpha)
{
	int		size_line;
	t_image	*ret;

	if (alpha < 0 || alpha > 255)
		error("initialize_image: Incorrect value %d for alpha.", alpha);
	if (!(ret = malloc(sizeof(t_image))))
		error("initialize_image: could not allocate image");
	ret->res = res;
	ret->ptr = mlx_new_image(game->conn->mlx_ptr, res.x, res.y);
	ret->data = mlx_get_data_addr(ret->ptr, &(ret->bpp), &size_line,
			&(ret->endian));
	ret->bpp /= 8;
	if (size_line != ret->res.x * ret->bpp)
	{
		error("initialize_game: unexpected size %d which is not equal to the "
				"horizontal resolution %d times the number of bytes per pixel "
				"%d in map image", size_line,
				ret->res.x, ret->bpp);
	}
	initialize_alpha(ret, alpha);
	if (!(ret->buffer = malloc(ret->bpp * ret->res.x * ret->res.y)))
		error("initialize_image: could not allocate buffer");
	return (ret);
}

t_image			*initialize_texture(t_game *game, char *path)
{
	int		size_line;
	t_image	*ret;
	char	*needle;

	if (!(needle = ft_strrchr(path, '.')))
		error("%s: File extension should be .xpm", path);
	if (ft_strcmp(needle, ".xpm") != 0)
		error("%s: File extension should be .xpm", path);
	if (!(ret = malloc(sizeof(t_image))))
		error("initialize_image: could not allocate image");
	if (!(ret->ptr = mlx_xpm_file_to_image(game->conn->mlx_ptr, path,
											&(ret->res.x), &(ret->res.y))))
		error("initialize_image: mlx_xpm_file_to_image failed");
	if (!(ret->data = mlx_get_data_addr(ret->ptr, &(ret->bpp),
											&size_line, &(ret->endian))))
		error("initialize_image: mlx_get_data_addr failed");
	ret->bpp /= 8;
	if (size_line != ret->res.x * ret->bpp)
	{
		error("initialize_game: unexpected size %d which is not equal to the "
				"horizontal resolution %d times the number of bytes per pixel "
				"%d in map image", size_line,
				ret->res.x, ret->bpp);
	}
	return (ret);
}

