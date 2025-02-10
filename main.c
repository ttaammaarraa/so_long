/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taabu-fe <taabu-fe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 22:27:12 by taabu-fe          #+#    #+#             */
/*   Updated: 2025/02/10 12:54:12 by taabu-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	error(char *str, char **map)
{
	if (map || *map)
		free_map(map);
	map = NULL;
	ft_putstr_fd(str, 2);
	exit(EXIT_FAILURE);
}

void	free_map(char **map)
{
	int	i;

	if (map)
	{
		i = 0;
		while (map[i])
		{
			free(map[i]);
			i++;
		}
		free(map);
	}
}

void	validate_map_chars(char **map)
{
	int	y;
	int	x;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] != '1' && map[y][x] != '0' && map[y][x] != 'P'
				&& map[y][x] != 'C' && map[y][x] != 'E' && map[y][x] != '\n')
				error("Error\nInvalid character in map.\n", map);
			x++;
		}
		y++;
	}
}

void	check_reachability(t_window *win)
{
	char	**map_copy;
	int		y;
	int		x;

	map_copy = copy_map(win->map);
	if (!map_copy)
		error("Error\nMem allocation failed check_reachability.\n", win->map);
	flood_fill(map_copy, win->player_x, win->player_y);
	y = 0;
	while (map_copy[y])
	{
		x = 0;
		while (map_copy[y][x])
		{
			if (map_copy[y][x] == 'C' || map_copy[y][x] == 'E')
			{
				free_map(map_copy);
				error("Error\nNot all collectibles or the exit are reachable.\n",
					win->map);
			}
			x++;
		}
		y++;
	}
	free_map(map_copy);
}

int	main(int argc, char **argv)
{
	t_window	win;

	if (not_ends_with_ber(argv[1]))
		return (0);
	if (argc != 2)
		error("Error\nWrong number of arguments.\n", NULL);
	win.map = read_map(argv[1]);
	if (!win.map)
		error("Error\nFailed to load map.\n", NULL);
	checks(&win);
	win.collectibles = count_collectibles(win.map);
	find_player_position(&win);
	win.moves = 0;
	check_reachability(&win);
	if (init_window(&win))
	{
		free_map(win.map);
		return (1);
	}
	load_images(&win);
	render_map(&win);
	mlx_hook(win.mlx_win, 2, 1L << 0, key_hook, &win);
	mlx_hook(win.mlx_win, 17, 0, close_window, &win);
	mlx_loop(win.mlx);
	return (0);
}
