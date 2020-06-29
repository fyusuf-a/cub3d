/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 16:32:45 by fyusuf-a          #+#    #+#             */
/*   Updated: 2020/06/29 12:19:33 by fyusuf-a         ###   ########.fr       */
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
# include "minilibX/mlx.h"

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
	int			allocated;
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
	/*char		*buffer;*/
	/*int			buffered;*/
}				t_image;

typedef struct	s_config {
	t_2d_int	resolution;
	t_image		*texture_no;
	t_image		*texture_so;
	t_image		*texture_we;
	t_image		*texture_ea;
	t_image		*texture_sprite;
	t_color		floor;
	t_color		ceiling;
}				t_config;

typedef struct	s_contact {
	t_2d		impact;
	int			cardinal_point;
}				t_contact;

typedef struct	s_connection {
	void		*mlx_ptr;
	void		*win_ptr;
}				t_connection;

/*
** A structure to remember which key was pressed
*/
typedef struct	s_keyboard {
	int			w;
	int			s;
	int			a;
	int			d;
	int			left;
	int			right;
	int			escape;
}				t_keyboard;

/*
** In the following structure, drawn_texture points to the current drawn
** texture (it is not mallocated per se) and screen_height is the height
** of the screen in raycasting (included here because it depends on macro
** SCREEN_DISTANCE and macros cannot have variables in the norm).
*/
typedef struct	s_game {
	t_keyboard		keyboard;
	t_map			map;
	t_player		player;
	t_config		config;
	t_list			*ray;
	t_image			*img_view;
	t_image			*img_map;
	t_image			*drawn_texture;
	t_connection	conn;
	double			screen_height;
	t_2d_int		pencil;
}				t_game;

/*
** key.c
*/
# define W		119
# define S		115
# define A		97
# define D		100
# define LEFT	65361
# define RIGHT	65363
# define ESCAPE	65307

int				key_pressed(int key);
int				key_released(int key);

/*
** file.c
*/

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
t_file			*open_file(const char *path);
void			close_file(t_file *file);

/*
** parse.c
*/
void	parse(const char *path);
/*
** Repeats action until EOF has been reached, or when action returns 0
** (indicating that action is done). Return is 0 if EOF is reached, 1 if
** action is done.
*/
int				repeat_gnl(t_file *file, int (*action) (t_file *file));
int				parse_natural(t_file *file);
int				gobble_while_elem(char *line, int start, const char *ens);
int				gobble_while_not_elem(char *line, int start, const char *ens);

/*
** parse_first.c
*/
void			parse_first_pass(t_file *file);

/*
** parse_second.c
*/
void			parse_second_pass(t_file *file);

/*
** parse_second2.c
*/
int				parse_second_pass_map(t_file *file);
void			parse_color(t_file *file, t_color *color);

/*
** parse_check.c
*/
void			parse_check(const t_file *file);

/*
** initialize.c
*/
void			initialize_game(const char *path);

/*
** free.c
*/
void			free_game(void);

/*
** free2.c
*/
void			free_ray(t_list *ray);
void			del(void *content);

/*
** initialize2.c
*/
t_image			*initialize_image(t_2d_int res, int alpha);
t_image			*initialize_texture(char *path);

/*
** minimap.c
*/
double			map_dim_to_pixel(t_image *image, int axis,
									double x);
t_2d_int		map_size_to_pixel(t_image *image, t_2d size);
t_2d_int		map_pos_to_pixel(t_image *image, t_2d pos);
void			draw_fov(const t_player *player, t_color color);
void			draw_minimap(t_player *old_player,
									t_player *new_player);

/*
** minimap2.c
*/
void			draw_walls_and_contours(void);
void			draw_player(t_player *player, t_color color);

/*
** draw.c
*/

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
void			draw(t_player *old_player, t_player *new_player);

/*
** draw2.c
*/
void			draw_line(t_image *img, t_line_params *params, t_2d_int point1,
							t_2d_int point2);

/*
** ray.c
*/

/*
** A helper structure for raycasting
** x is the intersection with an horizontal line of the ray
** y is the intersection with a vertical line of the ray
*/
# define HORIZONTAL 0
# define VERTICAL	1

# define NORTH	0
# define SOUTH	1
# define EAST	2
# define WEST	3

typedef struct	s_iter {
	t_contact	x;
	t_contact	y;
	int			current;
	double		tangent;
	t_2d		vector;
	int			cardinal_point;
	t_list		*ray;
	void		(*next_point_update)(const t_player *player,
							struct s_iter *iter);
}				t_iter;

t_2d			displaced(t_contact *contact);
t_list			*contact_with_wall(const t_player *player, t_iter *iter);
void			add_object_to_list(t_iter *iter, t_contact *contact);

/*
** ray2.c
*/
int				determine_cardinal_point(t_iter *iter);
void			initialize_iter(const t_player *player, t_iter *iter);
void			good_angle_update(const t_player *player, t_iter *iter);
void			bad_angle_update(const t_player *player, t_iter *iter);

/*
** view.c
*/
# define WALL_HEIGHT		2.0
# define EYE_HEIGHT			1.0
# define SCREEN_DISTANCE	0.1

int				convert_height(t_image *img, double height);
void			draw_view(t_player *new_player);
void			draw_texture(double perceived_height, double dist,
								int limit_above, int ignore_black);

/*
** view2.c
*/
void			draw_sprites_column(const t_player *temp_player,
						const t_player *new_player, const t_list *ray);

/*
** image.c
*/
/*void			copy_from_buffer(t_image *img);*/
t_color			color_from_image(t_image *img, t_2d_int pos);

/*
** bmp.c
*/
void			print_bmp(const t_image *img, const char *path);

/*
** utilities.c
*/
t_object		what_is(t_2d pos);
t_2d			what_cell(t_2d pos);
double			dist(t_2d point1, t_2d point2);
int				t_player_equal(t_player *player1, t_player *player2);
double			principal_measure(double angle);

/*
** utilities2.c
*/
double			abs_val(double x);
int				pos_equals(t_2d pos1, t_2d pos2);

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
t_color			g_red;
t_color			g_black;

t_game			g_game;
t_iter			g_iter;

#endif
