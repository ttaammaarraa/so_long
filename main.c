/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taabu-fe <taabu-fe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:01:57 by taabu-fe          #+#    #+#             */
/*   Updated: 2025/02/04 16:34:06 by taabu-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ends_with_ber(const char *str)
{
	size_t	len;

	len = ft_strlen(str);
	if (len < 4)
		return (0);
	if (ft_strncmp(str + len - 4, ".ber", 4) == 0)
		return (1);
	return (0);
}

char	**read_map(char *filename)
{
	int		fd;
	char	*line;
	char	**map;
	int		lines;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error("Error\nFailed to open the file.\n");
	map = NULL;
	lines = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (line[0] == '\0')
		{
			free(line);
			break ;
		}
		map = ft_realloc(map, lines * sizeof(char *), (lines + 2)
				* sizeof(char *));
		if (!map)
			error("Error\nMemory allocation failed.\n");
		map[lines++] = line;
		line = get_next_line(fd);

	}
	close(fd);
	if (!map)
		error("Error\nEmpty map file\n");
	map[lines] = NULL;
	return (map);
}

void	print_map(char **map)
{
	int	i;

	if (!map)
	{
		ft_putstr_fd("Error\nMap is NULL.\n", 2);
		return ;
	}
	ft_putstr_fd("Map Content:\n", 1);
	i = 0;
	while (map[i])
	{
		if (map[i])
			ft_putstr_fd(map[i], 1);
		else
			ft_putstr_fd("NULL line found.\n", 2);
		i++;
	}
}

void	error(char *str)
{
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

void	rectangular(char **map)
{
	int		i;
	size_t	first_line;

	i = 1;
	first_line = ft_strlen(map[0]);
	if (!first_line || first_line == 1)
	{
		free_map(map);
		error("Error\ninvalid map\n");
	}
	while (map[i])
	{
		if (ft_strlen(map[i]) != first_line)
		{
			free_map(map);
			error("Error\nnot rectangular\n");
		}
		i++;
	}
	if (i < 3)
	{
		free_map(map);
		error("Error\ninvalid map\n");
	}
}

void	is_valid_player(char **map)
{
	int	i;
	int	j;
	int	p;

	i = 1;
	p = 0;
	while (map[i])
	{
		j = 1;
		while (map[i][j])
		{
			if (map[i][j] == 'P')
				p++;
			j++;
		}
		i++;
	}
	if (p == 0 || p > 1)
	{
		free_map(map);
		error("Error\nShould have one player in the game\n");
	}
}

void	is_valid_exit(char **map)
{
	int	i;
	int	j;
	int	e;

	i = 1;
	e = 0;
	while (map[i])
	{
		j = 1;
		while (map[i][j])
		{
			if (map[i][j] == 'E')
				e++;
			j++;
		}
		i++;
	}
	if (e == 0 || e > 1)
	{
		free_map(map);
		error("Error\nShould have one exit in the game\n");
	}
}

void	is_valid_collectable(char **map)
{
	int	i;
	int	j;
	int	c;

	i = 1;
	c = 0;
	while (map[i])
	{
		j = 1;
		while (map[i][j])
		{
			if (map[i][j] == 'C')
				c++;
			j++;
		}
		i++;
	}
	if (c == 0)
	{
		free_map(map);
		error("Error\nShould have one collectable at least in the game\n");
	}
}

void	check_wall_1(char **map)
{
	int	i;
	int	width;
	int	height;

	i = 0;
	width = ft_strlen(map[0]) - 1;
	height = 0;
	while (map[height])
		height++;
	while (i < width)
	{
		if (map[0][i] != '1' || map[height - 1][i] != '1')
		{
			free_map(map);
			error("Error\nMap is not closed by walls\n");
		}
		i++;
	}
	check_wall_2(map);
}

void	check_wall_2(char **map)
{
	int	i;
	int	width;
	int	height;

	i = 0;
	width = ft_strlen(map[0]) - 1;
	height = 0;
	while (map[height])
		height++;
	while (i < height)
	{
		if (map[i][0] != '1' || map[i][width - 1] != '1')
		{
			free_map(map);
			error("Error\nMap is not closed by walls\n");
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	char	**map;
	t_window	win;

	if (argc != 2)
		error("Error\nToo Few Arguments\n");
	if (!ends_with_ber(argv[1]))
		error("Error\nThe file must have a .ber extension.\n");
	map = read_map(argv[1]);
	print_map(map);
	rectangular(map);
	check_wall_1(map);
	is_valid_exit(map);
	is_valid_collectable(map);
	is_valid_player(map);
    if (init_window(&win))
	{
        return (1);	
	}
	
	mlx_hook(win.mlx_win, 2, 1L<<0, key_hook1, &win);
	free_map(map);
	mlx_key_hook(win.mlx_win, key_hook, &win);
	mlx_hook(win.mlx_win, 17, 0, close_window, &win);
    mlx_loop(win.mlx);
	return (0);
}
