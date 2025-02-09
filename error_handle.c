/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taabu-fe <taabu-fe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 21:58:28 by taabu-fe          #+#    #+#             */
/*   Updated: 2025/02/08 22:58:27 by taabu-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

int	not_ends_with_ber(const char *str)
{
	size_t	len;
	char	*dot;

	dot = ft_strrchr(str, '.');
	len = ft_strlen(str);
	if (len < 4)
		return (0);
	if (!(ft_strcmp(dot, ".ber") == 0))
		error("Error\ninvalid expression\n");
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
