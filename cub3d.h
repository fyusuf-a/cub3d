/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 16:32:45 by fyusuf-a          #+#    #+#             */
/*   Updated: 2020/05/01 14:55:19 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D
# define CUB3D
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include "libft/libft.h"
# include "minilibx-linux/mlx.h"

# define GNL_ERROR		-1
# define GNL_FILE_END	0
# define GNL_DONE		1
# define GNL_NOT_DONE	2

/*
** minilibx keys
*/

# define W 119
# define S 115
# define A 97
# define D 100

/*
** Flag for error messages
*/
# define LINE_NB	1
# define COLUMN_NB	2

typedef struct	s_2d_int {
	int	x;
	int y;
}				t_2d_int;

typedef struct	s_2d {
	double	x;
	double	y;
}				t_2d;

/*
** angle is the oriented angle
*/

typedef struct	s_player {
	t_2d		pos;
	double		angle;
}				t_player;

typedef enum	e_object {
	VOID,
	WALL,
	OBJECT,
}				t_object;

typedef struct	s_map {
	t_2d_int	dim;
	t_object	**grid;
}				t_map;

typedef struct	s_color {
	int	r;
	int g;
	int b;
}				t_color;

typedef struct	s_config {
	t_2d_int	resolution;
	char		*texture_no_path;
	char		*texture_so_path;
	char		*texture_we_path;
	char		*texture_ea_path;
	char		*sprite_path;
	t_color		floor;
	t_color		ceiling;
}				t_config;

typedef struct	s_connection {
	void		*mlx_ptr;
	void		*win_ptr;
}				t_connection;

typedef struct	s_game {
	t_map			*map;
	t_player		*player;
	t_config		*config;
	t_connection	*conn;
}				t_game;

/*
** l is the line number, c the column number and file the content of the
** current line
*/

typedef struct	s_file {
	char		*path;
	char		*line;
	int			fd;
	int			l;
	int			c;
}				t_file;

/*
** parse_first.c
*/

t_file	*open_file(const char *path);
void	close_file(t_file *file);

/*
** parse_first.c
*/

void	parse(const char *path, t_game *game);
void	parse_first_pass(t_file *file, t_game *game);

/*
** parse_second.c
*/

void	parse_second_pass(t_file *file, t_game *game);

/*
** parse_check.c
*/

void	parse_check(const t_file *file, const t_game *game);

/*
** parse_utilities.c
*/

/*
** Repeats action until EOF has been reached, or when action returns 0
** (indicating that action is done). Return is 0 if EOF is reached, 1 if
** action is done.
*/
int	repeat_gnl(t_file *file, t_game *game,
		int (*action) (t_file *file, t_game *game));
int	parse_natural(t_file *file);
int	ft_strlen_while_elem(char *line, int start, const char *ens);
int	ft_strlen_while_not_elem(char *line, int start, const char *ens);
int	gobble_while_elem(char *line, int start, const char *ens);
int	gobble_while_not_elem(char *line, int start, const char *ens);

/*
** utilities.c
*/

void	initialize_game(const char* path, t_game *game);

/*
** error.c
*/
void	error(const char *msg, ...);
void	parse_error(const t_file *file, int flag, const char *msg, ...);

 /*
 ** debug.c
 */
 void	print_config(const t_config *c);
 void	print_map(const t_map *m);
 void	print_player(const t_player *p);

#endif
