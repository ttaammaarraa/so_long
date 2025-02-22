/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taabu-fe <taabu-fe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 22:18:15 by taabu-fe          #+#    #+#             */
/*   Updated: 2025/02/22 20:47:25 by taabu-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
			ft_printf("Moves: %d\n", ++win->moves);
			close_window(win);
			return ;
		}
	}
	win->player_x = new_x;
	win->player_y = new_y;
	win->moves++;
	ft_printf("Moves: %d\n", win->moves);
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
