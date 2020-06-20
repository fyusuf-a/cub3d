/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 09:08:44 by fyusuf-a          #+#    #+#             */
/*   Updated: 2020/06/20 11:08:19 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_file	*open_file(const char *path)
{
	t_file *ret;

	ret = malloc(sizeof(t_file));
	ret->line = NULL;
	ret->path = ft_strdup(path);
	if ((ret->fd = open(path, O_RDONLY)) < 0)
		error("Could not open file \"%s\"", path);
	ret->l = 0;
	ret->c = 0;
	return (ret);
}

void	close_file(t_file *file)
{
	close(file->fd);
}
