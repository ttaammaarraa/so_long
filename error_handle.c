/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taabu-fe <taabu-fe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 21:58:28 by taabu-fe          #+#    #+#             */
/*   Updated: 2025/02/10 13:32:00 by taabu-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	not_ends_with_ber(const char *str)
{
	size_t	len;
	char	*dot;

	dot = ft_strrchr(str, '.');
	len = ft_strlen(str);
	if (len < 4)
		return (0);
	if (!(ft_strcmp(dot, ".ber") == 0))
		error("Error\ninvalid expression\n", NULL);
	return (0);
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
			error("Error\nMap is not closed by walls\n", map);
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
			error("Error\nMap is not closed by walls\n", map);
		i++;
	}
}

char	**copy_map(char **map)
{
	int		i;
	int		j;
	char	**copy;

	i = 0;
	copy = NULL;
	while (map[i])
		i++;
	copy = malloc(sizeof(char *) * (i + 1));
	if (!copy)
		return (NULL);
	j = 0;
	while (j < i)
	{
		copy[j] = ft_strdup(map[j]);
		if (!copy[j])
		{
			free_map(copy);
			return (NULL);
		}
		j++;
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
