/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 17:29:13 by fyusuf-a          #+#    #+#             */
/*   Updated: 2020/06/15 17:32:25 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void
	parse(const char *path)
{
	t_file	*file;
	char	*needle;

	file = open_file(path);
	if (!(needle = ft_strrchr(path, '.')))
		error("%s: File extension should be .cub", path);
	if (ft_strcmp(needle, ".cub") != 0)
		error("%s: File extension should be .cub", path);
	parse_first_pass(file);
	close_file(file);
	file = open_file(path);
	parse_second_pass(file);
	parse_check(file);
	close_file(file);
}

/*
** Repeats action until EOF has been reached, or when action returns
** GNL_DONE (indicating that action is done). Return is GNL_FILE_END
** if EOF is reached, GNL_DONE if action is done.
*/

int
	repeat_gnl(t_file *file, int (*action) (t_file *file))
{
	static int	action_already_run = 0;
	int			ret_gnl;

	if (action_already_run || !file->line)
	{
		if (file->line)
			free(file->line);
		ret_gnl = get_next_line(file->fd, &(file->line));
		file->l++;
		if (ret_gnl == -1)
			parse_error(file, LINE_NB, "get_next_line returned an error code");
		if (ret_gnl == 0)
		{
			action(file);
			return (GNL_FILE_END);
		}
	}
	file->c = 0;
	if (action(file) == GNL_DONE)
	{
		action_already_run = 0;
		return (GNL_DONE);
	}
	action_already_run = 1;
	return (repeat_gnl(file, action));
}

/*
** Parses a non-negative number. Returns -1 if current character is not a digit.
*/

int
	parse_natural(t_file *file)
{
	int		number;
	char	c;

	c = file->line[file->c];
	if (!('0' <= c && c <= '9'))
		return (-1);
	number = 0;
	while ('0' <= (c = file->line[file->c]) && c <= '9')
	{
		number = 10 * number + c - '0';
		file->c++;
	}
	return (number);
}

int
	gobble_while_elem(char *line, int start, const char *ens)
{
	while (line[start] && ft_elem(line[start], ens))
		start++;
	return (start);
}

int
	gobble_while_not_elem(char *line, int start, const char *ens)
{
	while (line[start] && !ft_elem(line[start], ens))
		start++;
	return (start);
}
