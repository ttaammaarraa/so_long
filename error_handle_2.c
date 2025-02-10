/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taabu-fe <taabu-fe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:40:30 by taabu-fe          #+#    #+#             */
/*   Updated: 2025/02/10 13:32:30 by taabu-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	checks(t_window *win)
{
	validate_map_chars(win->map);
	rectangular(win->map);
	check_wall_1(win->map);
	is_valid_exit(win->map);
	is_valid_collectable(win->map);
	is_valid_player(win->map);
}

void	check_size(t_window *win, int height, int width)
{
	int	w;
	int	h;

	mlx_get_screen_size(win->mlx, &w, &h);
	if ((height * 60) > h || (width * 60) > w)
	{
		mlx_destroy_display(win->mlx);
		free(win->mlx);
		error("Error\nhahahah you can't do that :)\n", win->map);
	}
}

int	close_window(t_window *win)
{
	mlx_destroy_image(win->mlx, win->img.floor);
	mlx_destroy_image(win->mlx, win->img.wall);
	mlx_destroy_image(win->mlx, win->img.player);
	mlx_destroy_image(win->mlx, win->img.collectable);
	mlx_destroy_image(win->mlx, win->img.exit);
	mlx_destroy_window(win->mlx, win->mlx_win);
	mlx_destroy_display(win->mlx);
	free(win->mlx);
	free_map(win->map);
	exit(EXIT_SUCCESS);
	return (0);
}
