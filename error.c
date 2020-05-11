/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 11:36:26 by fyusuf-a          #+#    #+#             */
/*   Updated: 2020/05/01 16:46:13 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void
	error(const char *msg, ...)
{
	va_list	args;

	va_start(args, msg);
	ft_dprintf(2, "Error\n");
	ft_zprintf(2, msg, &args);
	va_end(args);
	ft_dprintf(2, "\n");
	exit(EXIT_FAILURE);
}

void
	parse_error(const t_file *file, int flag, const char *msg, ...)
{
	va_list	args;

	ft_dprintf(2, "Error\n");
	va_start(args, msg);
	ft_dprintf(2, "%s ", file->path);
	if (flag & LINE_NB)
	{
		ft_dprintf(2, "(line %d", file->l);
		if (flag & COLUMN_NB)
			ft_dprintf(2, ", col %d", file->c + 1);
		ft_dprintf(2, ")");
	}
	ft_dprintf(2, ": ");
	ft_zprintf(2, msg, &args);
	va_end(args);
	ft_dprintf(2, "\n");
	exit(EXIT_FAILURE);
}
