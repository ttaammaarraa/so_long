/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taabu-fe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 02:21:10 by taabu-fe          #+#    #+#             */
/*   Updated: 2024/11/11 02:21:10 by taabu-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stddef.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

int		t_strlen(char *str);
char	*t_strchr(const char *s, int c);
char	*t_strjoin(char *str1, char *str2);
char	*t_strdup(char *str1);
char	*t_substr(char *s, unsigned int start, size_t len);
char	*get_next_line(int fd);
void	*t_free(char **buff);

#endif
