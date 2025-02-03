/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taabu-fe <taabu-fe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:02:28 by taabu-fe          #+#    #+#             */
/*   Updated: 2025/02/03 13:49:06 by taabu-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
#define SO_LONG_H

#include "./libft/libft.h"
#include "./minilibx-linux/mlx.h"
#include "./get_next_line/get_next_line.h"
//#include <mlx.h>
#include <fcntl.h>
#include <unistd.h> 
#include <stdio.h>

typedef struct s_window
{
    void    *mlx;
    void    *mlx_win;
}   t_window;

int	    ends_with_ber(const char *str);
char	**read_map(char *filename);
void	print_map(char **map);
void	error(char *str);
void	free_map(char **map);
void	rectangular(char **map);
void	is_valid_player(char **map);
void	is_valid_exit(char **map);
void	is_valid_collectable(char **map);
void	check_wall_1(char **map);
void	check_wall_2(char **map);

#endif
