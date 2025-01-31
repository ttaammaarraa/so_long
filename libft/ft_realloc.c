/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taabu-fe <taabu-fe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 23:13:50 by taabu-fe          #+#    #+#             */
/*   Updated: 2025/01/30 17:18:41 by taabu-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 /*#include "libft.h"

void    *ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
        void    *str;

        str = malloc (new_size);
        if (!str)
        {
                free (ptr);
                return (NULL);
        }
        ft_memcpy(str, ptr, old_size);
        free (ptr);
        return (str);
}*/
#include "libft.h"

/*void    *ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
    void    *str;

    // إذا كان new_size == 0, يجب تحرير ptr وإرجاع NULL
    if (new_size == 0)
    {
        free(ptr);
        return NULL;
    }

    // إذا كان ptr == NULL, فقط قم بتخصيص new_size كما يفعل malloc
    if (!ptr)
        return malloc(new_size);

    // تخصيص مساحة جديدة
    str = malloc(new_size);
    if (!str)
        return NULL;  // لم نقم بتحرير ptr لأنه قد لا يزال يحتوي على بيانات مهمة

    // نسخ البيانات بحجم الحد الأدنى بين old_size و new_size
    ft_memcpy(str, ptr, (old_size < new_size) ? old_size : new_size);

    // تحرير الذاكرة القديمة
    free(ptr);

    return str;
}*/

#include "libft.h"

void    *ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
    void    *new_ptr;

    if (new_size == 0)
    {
        free(ptr);
        return (NULL);
    }
    if (!ptr)
        return (malloc(new_size));

    new_ptr = malloc(new_size);
    if (!new_ptr)
    {
        free(ptr);
        return (NULL);
    }

    ft_memcpy(new_ptr, ptr, old_size < new_size ? old_size : new_size);
    free(ptr);
    return (new_ptr);
}


