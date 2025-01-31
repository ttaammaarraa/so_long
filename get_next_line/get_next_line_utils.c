/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taabu-fe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 02:17:24 by taabu-fe            #+#    #+#           */
/*   Updated: 2024/11/11 02:17:24 by taabu-fe           ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	t_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*t_strchr(const char *s, int c)
{
	char			cc;
	unsigned int	i;

	i = 0;
	cc = (char) c;
	while (s[i] != '\0')
	{
		if (s[i] == cc)
			return ((char *)&s[i]);
		i++;
	}
	if (cc == '\0')
		return ((char *)&s[i]);
	return (NULL);
}

char	*t_strjoin(char *str1, char *str2)
{
	char	*str;
	int		i;
	int		j;

	i = -1;
	j = -1;
	if (!str1 && !str2)
		return (NULL);
	str = malloc((t_strlen(str1) + t_strlen(str2) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (str1[++i])
		str[i] = str1[i];
	while (str2[++j])
		str[i++] = str2[j];
	str[i] = '\0';
	t_free (&str1);
	return (str);
}

char	*t_strdup(char *str1)
{
	int		i;
	char	*dest;

	i = 0;
	dest = malloc((t_strlen(str1) + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	while (str1[i])
	{
		dest[i] = str1[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*t_substr(char *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;
	size_t	len_s;

	len_s = t_strlen(s);
	if (!s || start >= len_s)
		return (t_strdup(""));
	if (len > t_strlen(s) - start)
		len = len_s - start;
	substr = malloc((len + 1) * sizeof(char));
	if (!substr)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}
