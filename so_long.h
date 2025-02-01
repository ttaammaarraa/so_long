/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taabu-fe <taabu-fe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:02:28 by taabu-fe          #+#    #+#             */
/*   Updated: 2025/02/01 22:08:55 by taabu-fe         ###   ########.fr       */
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

void    free_map(char **map);
void    error(char *str);
void	check_wall_2(char **map);
#endif
