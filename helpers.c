/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taabu-fe <taabu-fe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 21:38:48 by taabu-fe          #+#    #+#             */
/*   Updated: 2025/02/10 12:20:19 by taabu-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	rectangular(char **map)
{
	int		i;
	size_t	first_line;

	i = 1;
	first_line = ft_strlen(map[0]);
	if (!first_line || first_line == 1)
		error("Error\ninvalid map\n", map);
	while (map[i])
	{
		if (ft_strlen(map[i]) != first_line)
			error("Error\nnot rectangular\n", map);
		i++;
	}
	if (i < 3)
		error("Error\ninvalid map\n", map);
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
		error("Error\nShould have one player in the game\n", map);
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
		error("Error\nShould have one exit in the game\n", map);
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
		error("Error\nShould have one collectable at least in the game\n", map);
}

int	count_collectibles(char **map)
{
	int	x;
	int	y;
	int	count;

	count = 0;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'C')
				count++;
			x++;
		}
		y++;
	}
	return (count);
}
