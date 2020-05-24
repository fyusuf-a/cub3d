/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 16:32:45 by fyusuf-a          #+#    #+#             */
/*   Updated: 2020/05/24 21:16:17 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <math.h>
# include <X11/Xlib.h>
# include "libft/libft.h"
# include "minilibx-linux/mlx.h"

# define GNL_ERROR		-1
# define GNL_FILE_END	0
# define GNL_DONE		1
# define GNL_NOT_DONE	2

# ifndef M_PI
#  define M_PI 3.14159265359
# endif

/*
** Axis numbers
*/

# define YAXIS 0
# define XAXIS 1

/*
** minilibx keys
*/

# define W		119
# define S		115
# define A		97
# define D		100
# define LEFT	65361
# define RIGHT	65363

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
	UNDEFINED,
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

/*
** Contrary to mlx, here bpp is Byte per pixel and not Bit per pixel
*/
typedef struct	s_image {
	int			bpp;
	t_2d_int	res;
	int			endian;
	void		*ptr;
	char		*data;
	char		*buffer;
	int			buffered;
}				t_image;

typedef struct	s_config {
	t_2d_int	resolution;
	char		*texture_no_path;
	t_image		*texture_no;
	char		*texture_so_path;
	t_image		*texture_so;
	char		*texture_we_path;
	t_image		*texture_we;
	char		*texture_ea_path;
	t_image		*texture_ea;
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
	t_image			*img_view;
	t_image			*img_map;
}				t_game;

/*
** l is the line number, c the column number and file the content of the
** current line
*/

typedef struct	s_file {
	char		*path;
	char		*line;
	int			gnl_ret;
	int			fd;
	int			l;
	int			c;
}				t_file;

/*
** parse_first.c
*/

t_file			*open_file(const char *path);
void			close_file(t_file *file);

/*
** parse_first.c
*/

void			parse(const char *path, t_game *game);
void			parse_first_pass(t_file *file, t_game *game);

/*
** parse_second.c
*/

void			parse_second_pass(t_file *file, t_game *game);

/*
** parse_second2.c
*/

int				parse_second_pass_map(t_file *file, t_game *game);

/*
** parse_check.c
*/

void			parse_check(const t_file *file, const t_game *game);

/*
** parse_utilities.c
*/

/*
** Repeats action until EOF has been reached, or when action returns 0
** (indicating that action is done). Return is 0 if EOF is reached, 1 if
** action is done.
*/
int				repeat_gnl(t_file *file, t_game *game,
							int (*action) (t_file *file, t_game *game));
int				parse_natural(t_file *file);
int				gobble_while_elem(char *line, int start, const char *ens);
int				gobble_while_not_elem(char *line, int start, const char *ens);

/*
** initialize.c
*/

void			initialize_game(const char *path, t_game *game);

/*
** initialize2.c
*/
t_image			*initialize_image(t_game *game, t_2d_int res, int alpha);
t_image			*initialize_texture(t_game *game, char *path);

/*
** minimap.c
*/

double			map_dim_to_pixel(t_game *game, t_image *image, int axis,
									double x);
t_2d_int		map_size_to_pixel(t_game *game, t_image *image, t_2d size);
t_2d_int		map_pos_to_pixel(t_game *game, t_image *image, t_2d pos);
void			draw_fov(t_game *game, t_player *player, t_color color);
void			draw_minimap(t_game *game, t_player *old_player,
									t_player *new_player);

/*
** minimap2.c
*/
void			draw_walls_and_contours(t_game *game);
void			draw_player(t_game *game, t_player *player, t_color color);

/*
** draw.c
*/

/*
** Working with image buffer or not
*/

# define UNBUFFERED	0
# define BUFFERED 	1

/*
** Helper structure for drawing lines
*/
typedef struct	s_line_params {
	int			thickness;
	t_color		color;
}				t_line_params;
void			draw_pixel(t_image *img, t_color color, t_2d_int pos);
void			draw_rectangle(t_image *img, t_color color, t_2d_int origin,
							t_2d_int dim);
void			draw_rectangle_from_center(t_image *img, t_color color,
							t_2d_int center, t_2d_int dim);
void			draw(t_game *game, t_player *old_player, t_player *new_player);

/*
** ray2.c
*/

void			draw_line(t_image *img, t_line_params *params, t_2d_int point1,
							t_2d_int point2);

/*
** ray.c
*/

typedef struct	s_contact {
	t_2d		impact;
	int			cardinal_point;
}				t_contact;
/*
** Helper structure for performance while raycasting
*/
typedef struct	s_direction {
	double		tangent;
	t_2d		vector;
}				t_direction;
/*
** Another helper structure for performance while raycasting
*/
typedef struct	s_dda {
	t_contact	*x;
	t_contact	*y;
}				t_dda;
# define NORTH	0
# define SOUTH	1
# define EAST	2
# define WEST	3
t_contact		contact_with_wall(t_game *game, t_player *player);

/*
** ray2.c
*/

t_contact		*next_point_on_vertical_line(t_game *game, t_player *player,
										t_dda* dda, t_direction *direction);
t_contact		*next_point_on_horizontal_line(t_game *game, t_player *player,
										t_dda* dda, t_direction *direction);
/*
** view.c
*/

# define WALL_HEIGHT		2.0
# define SCREEN_WIDTH		1.0
# define EYE_HEIGHT			1.0
# define SCREEN_DISTANCE	0.1

void			draw_view(t_game *game, t_player *new_player);

/*
** image.c
*/

void			copy_from_buffer(t_image *img);

/*
** utilities.c
*/
t_object		what_is(t_game *game, t_2d pos);
t_2d			what_cell(t_2d pos);
double			dist(t_2d point1, t_2d point2);
int				t_player_equal(t_player *player1, t_player *player2);
double			principal_measure(double angle);

/*
** error.c
*/

void			error(const char *msg, ...);
void			parse_error(const t_file *file, int flag, const char *msg, ...);

/*
** debug.c
*/

void			print_config(const t_config *c);
void			initialize_map(const t_map *m);
void			print_player(const t_player *p);

t_color			g_white;
t_color			g_black;
t_color			g_red;
t_color			g_blue;
t_color			g_green;

#endif
