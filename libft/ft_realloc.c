/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taabu-fe <taabu-fe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 23:13:50 by taabu-fe          #+#    #+#             */
/*   Updated: 2025/02/11 11:23:44 by taabu-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*str;

	str = malloc(new_size);
	if (!str)
	{
		free(ptr);
		return (NULL);
	}
	ft_memcpy(str, ptr, old_size);
	free(ptr);
	return (str);
}
