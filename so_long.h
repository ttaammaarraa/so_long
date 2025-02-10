/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taabu-fe <taabu-fe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:02:28 by taabu-fe          #+#    #+#             */
/*   Updated: 2025/02/10 17:10:26 by taabu-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "./get_next_line/get_next_line.h"
# include "./libft/libft.h"
# include "./ft_printf/ft_printf.h"
# include "./minilibx-linux/mlx.h"
//# include <mlx.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>

typedef struct s_data
{
	void	*img;
	void	*player;
	void	*wall;
	void	*floor;
	void	*collectable;
	void	*exit;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_data;

typedef struct s_window
{
	void	*mlx;
	void	*mlx_win;
	int		img_width;
	int		img_height;
	int		collectibles;
	int		player_x;
	int		player_y;
	int		moves;
	t_data	img;
	char	**map;
}			t_window;


int			not_ends_with_ber(const char *str);
char		**read_map(char *filename);
void		error(char *str, char **map);
void		free_map(char **map);
void		rectangular(char **map);
void		is_valid_player(char **map);
void		is_valid_exit(char **map);
void		is_valid_collectable(char **map);
void		check_wall_1(char **map);
void		check_wall_2(char **map);
void		load_images(t_window *win);
int			key_hook(int keycode, t_window *win);
int			close_window(t_window *win);
int			init_window(t_window *win);
void		load_images(t_window *win);
int			key_hook(int keycode, t_window *win);
void		render_map(t_window *win);
char		**read_map1(int fd);
int			count_collectibles(char **map);
void		find_player_position(t_window *win);
void		move_player(t_window *win, int new_x, int new_y);
void		check_reachability(t_window *win);
char		**copy_map(char **map);
void		flood_fill(char **map, int x, int y);
void		checks(t_window *win);
void		validate_map_chars(char **map);
void		error_without_free(char *str);
void		check_size(t_window *win, int height, int width);
#endif
