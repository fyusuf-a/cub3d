/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyusuf-a <fyusuf-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 09:14:47 by fyusuf-a          #+#    #+#             */
/*   Updated: 2020/05/01 14:55:09 by fyusuf-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
# include <X11/Xlib.h>

int	draw(t_game *game)
{
	t_2d_int	pixel;

	pixel.x = (game->player->pos.x / (0.5 + game->map->dim.x)) * game->config->resolution.x;
	pixel.y = (game->player->pos.y / (0.5 + game->map->dim.y)) * game->config->resolution.y;
	mlx_pixel_put(game->conn->mlx_ptr, game->conn->win_ptr, pixel.x, pixel.y, 0xFFFFFF);
	return (EXIT_SUCCESS);
}

int	key_hook(int key, t_game *game)
{
	double step = 0.1;
	if (key == W)
		game->player->pos.y - step > 0 ? game->player->pos.y -= step : 0;
	if (key == S)
		game->player->pos.y + step < game->map->dim.x + 0.5 ? game->player->pos.y += step : 0;
	if (key == A)
		game->player->pos.x - step > 0 ? game->player->pos.x -= step : 0;
	if (key == D)
		game->player->pos.x + step < game->map->dim.x + 0.5 ? game->player->pos.x += step : 0;
	draw(game);
	return (EXIT_SUCCESS);
}

int	main(int argc, char *argv[])
{
	t_game	game;
	char	*line;

	(void) game;
	if (argc != 2)
		error("Usage: cub3d map.cub");
	int fd = open(argv[1],O_RDONLY);
	int ret = get_next_line(fd, &line);
	ft_printf("%d->%s<-\n", ret, line);

	/*initialize_game(argv[1], &game);*/
	/*mlx_hook(game.conn->win_ptr, KeyPress, KeyPressMask, key_hook, &game);*/
	/*mlx_key_hook(game.conn->win_ptr, key_hook, &game);*/
	/*mlx_loop_hook(game.conn->win_ptr, loop_hook, &game);*/
	/*mlx_loop(game.conn->mlx_ptr);*/
	return (EXIT_SUCCESS);
}

/*int main()*/
/*{*/
	/*void	*conn;*/
	/*void	*window;*/

	/*window = mlx_new_window();*/
	/*mlx_loop(window, );*/
	/*return (0);*/
/*}*/
