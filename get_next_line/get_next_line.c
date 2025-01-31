/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taabu-fe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 09:09:17 by taabu-fe          #+#    #+#             */
/*   Updated: 2024/11/13 09:09:19 by taabu-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*t_free(char **buff)
{
	if (*buff)
	{
		free(*buff);
		*buff = NULL;
	}
	return (NULL);
}

char	*fill(int fd, char *re, char *buff, int *bytes_read)
{
	char	*temp;

	*bytes_read = read (fd, buff, BUFFER_SIZE);
	if (*bytes_read == -1)
	{
		t_free(&buff);
		return (t_free(&re));
	}
	buff[*bytes_read] = '\0';
	if (re)
	{
		temp = t_strjoin(re, buff);
		if (!temp)
		{
			t_free(&buff);
			return (t_free(&re));
		}
		re = temp;
	}
	else
		re = t_strdup(buff);
	if (!re)
		return (t_free(&buff));
	return (re);
}

char	*read_line(int fd, char *re)
{
	char	*buff;
	int		bytes_read;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		re = fill(fd, re, buff, &bytes_read);
		if (!re)
			return (NULL);
		if (t_strchr(re, '\n'))
			break ;
	}
	t_free(&buff);
	return (re);
}

char	*extract(char **re, char **line)
{
	char	*temp;
	char	*newline_pos;

	newline_pos = t_strchr(*re, '\n');
	if (newline_pos)
	{
		*line = t_substr(*re, 0, newline_pos - *re + 1);
		if (!*line)
			return (t_free(re));
		temp = t_strdup(newline_pos + 1);
		if (!temp)
		{ 
			t_free(line);
			return (t_free(re));
		}
		t_free(re);
		*re = temp;
	}
	else
	{
		*line = t_strdup(*re);
		t_free(re);
		*re = NULL;
	}
	return (*line);
}

char	*get_next_line(int fd)
{
	static char	*re = NULL;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	re = read_line(fd, re);
	if (!re)
		return (NULL);
	if (t_strchr(re, '\n'))
	{
		if (!extract(&re, &line))
			return (NULL);
		return (line);
	}
	if (*re)
	{
		line = t_strdup(re);
		t_free(&re);
		return (line);
	}
	t_free(&re);
	return (NULL);
}
/*
int	main(void)
{
	int		fd;
	char	*str;

	fd = open("ggg.txt", O_RDONLY| O_CREAT);
	if (fd == -1)
		return (-1);
	while (1)
	{
		str = get_next_line(fd);
		if (str == NULL)
				break ;
		printf("%s",str);
		free (str);
	}
	if(close(fd) < 0)
			return (-1);
	return (0);
}*/