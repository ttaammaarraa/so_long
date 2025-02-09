/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taabu-fe <taabu-fe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 14:47:27 by taabu-fe          #+#    #+#             */
/*   Updated: 2025/02/09 14:48:18 by taabu-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**read_map1(int fd)
{
	char	*line;
	char	**map;
	int		lines;

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
		map = ft_realloc(map, lines * sizeof(char *), (lines + 2) * sizeof(char *));
		if (!map)
			error("Error\nMemory allocation failed.\n");
		map[lines++] = line;
		line = get_next_line(fd);
	}
	if (!map)
		error("Error\nEmpty map file\n");
	map[lines] = NULL;
	return (map);
}

char	**read_map(char	*filename)
{
	char	**map;
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error("Error\nFailed to open the file.\n");
	map = read_map1 (fd);
	close (fd);
	return (map);
}
