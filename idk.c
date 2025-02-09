/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   idk.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taabu-fe <taabu-fe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 22:18:15 by taabu-fe          #+#    #+#             */
/*   Updated: 2025/02/08 22:58:53 by taabu-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
//for loops
char	**copy_map(char **map)
{
	int		i;
	char	**copy;

	i = 0;
	copy = NULL;
	while (map[i])
		i++;
	copy = malloc(sizeof(char *) * (i + 1));
	if (!copy)
		return (NULL);
	for (int j = 0; j < i; j++)
	{
		copy[j] = ft_strdup(map[j]);
		if (!copy[j])
		{
			for (int k = 0; k < j; k++)
				free(copy[k]);
			free(copy);
			return (NULL);
		}
	}
	copy[i] = NULL;
	return (copy);
}

void	flood_fill(char **map, int x, int y)
{
	if (y < 0 || x < 0 || !map[y] || x >= (int)ft_strlen(map[y]))
		return ;
	if (map[y][x] == '1' || map[y][x] == 'V')
		return ;
	map[y][x] = 'V';
	flood_fill(map, x + 1, y);
	flood_fill(map, x - 1, y);
	flood_fill(map, x, y + 1);
	flood_fill(map, x, y - 1);
}


void	move_player(t_window *win, int new_x, int new_y)
{
	if (win->map[new_y][new_x] == '1')
		return ;
	if (win->map[new_y][new_x] == 'C')
	{
		win->collectibles--;
		win->map[new_y][new_x] = '0';
	}
	if (win->map[new_y][new_x] == 'E')
	{
		if (win->collectibles == 0)
		{
			close_window(win);
			return ;
		}
	}
	win->player_x = new_x;
	win->player_y = new_y;
	win->moves++;
	//انتبهي برنت اف
	printf("Moves: %d\n", win->moves);
	render_map(win);
}

void	find_player_position(t_window *win)
{
	int	y;
	int	x;

	y = 0;
	while (win->map[y])
	{
		x = 0;
		while (win->map[y][x])
		{
			if (win->map[y][x] == 'P')
			{
				win->player_x = x;
				win->player_y = y;
				win->map[y][x] = '0';
				return ;
			}
			x++;
		}
		y++;
	}
}
