/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taabu-fe <taabu-fe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:18:42 by taabu-fe          #+#    #+#             */
/*   Updated: 2025/02/10 17:17:53 by taabu-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	init_window(t_window *win)
{
	int	height;
	int	width;

	if (!win || !win->map || !win->map[0])
		return (1);
	width = ft_strlen(win->map[0]) - 1;
	height = 0;
	while (win->map[height])
		height++;
	win->mlx = mlx_init();
	check_size(win, height, width);
	if (!win->mlx)
		return (1);
	win->mlx_win = mlx_new_window(win->mlx, width * 60, height * 60, "so_long");
	if (!win->mlx_win)
	{
		mlx_destroy_display(win->mlx);
		free(win->mlx);
		return (1);
	}
	return (0);
}

void	load_images(t_window *win)
{
	win->img.player = mlx_xpm_file_to_image(win->mlx, "./textures/player.xpm",
			&win->img_width, &win->img_height);
	win->img.wall = mlx_xpm_file_to_image(win->mlx, "./textures/wall.xpm",
			&win->img_width, &win->img_height);
	win->img.floor = mlx_xpm_file_to_image(win->mlx, "./textures/floor.xpm",
			&win->img_width, &win->img_height);
	win->img.collectable = mlx_xpm_file_to_image(win->mlx,
			"./textures/collectable.xpm", &win->img_width, &win->img_height);
	win->img.exit = mlx_xpm_file_to_image(win->mlx, "./textures/exit.xpm",
			&win->img_width, &win->img_height);
	if (!win->img.player || !win->img.wall || !win->img.floor
		|| !win->img.collectable || !win->img.exit)
	{
		error_without_free("Error\nFailed to load one or more images.\n");
	}
}

void	render_map_1(t_window *win, int x, int y, void **img)
{
	if (win->map[y][x] == '\n')
		return ;
	*img = win->img.floor;
	if (win->map[y][x] == '1')
		*img = win->img.wall;
	else if (win->map[y][x] == 'C')
		*img = win->img.collectable;
	else if (win->map[y][x] == 'E')
	{
		if (win->collectibles == 0)
			*img = win->img.exit;
		else
			*img = win->img.floor;
	}
}

void	render_map(t_window *win)
{
	int		x;
	int		y;
	void	*img;

	img = NULL;
	if (!win->map)
		error("Error\nMap is not initialized.\n", win->map);
	y = 0;
	while (win->map[y])
	{
		x = 0;
		while (win->map[y][x])
		{
			render_map_1(win, x, y, &img);
			mlx_put_image_to_window(win->mlx, win->mlx_win, img, x * 60, y
				* 60);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(win->mlx, win->mlx_win, win->img.player,
		win->player_x * 60, win->player_y * 60);
}

int	key_hook(int keycode, t_window *win)
{
	if (keycode == XK_Escape || keycode == XK_q)
		close_window(win);
	else if (keycode == XK_w || keycode == XK_Up)
		move_player(win, win->player_x, win->player_y - 1);
	else if (keycode == XK_s || keycode == XK_Down)
		move_player(win, win->player_x, win->player_y + 1);
	else if (keycode == XK_a || keycode == XK_Left)
		move_player(win, win->player_x - 1, win->player_y);
	else if (keycode == XK_d || keycode == XK_Right)
		move_player(win, win->player_x + 1, win->player_y);
	return (0);
}
