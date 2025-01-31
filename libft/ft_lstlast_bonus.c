/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taabu-fe <taabu-fe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 13:26:07 by taabu-fe          #+#    #+#             */
/*   Updated: 2025/01/12 13:26:08 by taabu-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//#include <stdio.h>
t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

/* int main()
{
	int data = 10;
	t_list *p = ft_lstnew(&data);
	int data2 = 50;
	t_list *s = ft_lstnew(&data2);
	p->next = s;
	t_list *last = ft_lstlast(p);
	printf("%d" , *(int *)last->content);

} */