/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taabu-fe <taabu-fe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 14:41:03 by taabu-fe          #+#    #+#             */
/*   Updated: 2025/02/03 17:20:15 by taabu-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	init_window(t_window *win)
{
	win->mlx = mlx_init();
	if(!win->mlx)
		return (1);
	win->mlx_win = mlx_new_window(win->mlx, 900, 800, "so_long");
	if(!win->mlx_win)
	{
		free(win->mlx);
		return (1);
	}
	return (0);
}
int main(void)
{
    t_window win;

    if (init_window(&win))
        return (1);
    mlx_loop(win.mlx);
/*     mlx_destroy_window(win.mlx, win.mlx_win);
    mlx_destroy_display(win.mlx); */
    free(win.mlx);
}
