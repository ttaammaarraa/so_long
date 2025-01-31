/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taabu-fe <taabu-fe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:01:57 by taabu-fe          #+#    #+#             */
/*   Updated: 2025/01/30 21:05:52 by taabu-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int ends_with_ber(const char *str)
{
    size_t len = ft_strlen(str);
    
    if (len < 4)
        return 0;
    if (ft_strncmp(str + len - 4, ".ber", 4) == 0)
        return 1;
    return 0;
}

char **read_map(char *filename)
{
    int fd;
    char *line;
    char **map;
    int lines;

    fd = open(filename, O_RDONLY);
    if (fd < 0)
        error("Error\nFailed to open the file.\n");
    map = NULL;
    lines = 0;
    while ((line = get_next_line(fd)))
    {
        if (line[0] == '\0')  // إذا السطر فارغ، تجاهله
        {
            free(line);  // تحرير الذاكرة
            break;
        }
        map = ft_realloc(map, lines * sizeof(char *), (lines + 2) * sizeof(char *));
        if (!map)
            error("Error\nMemory allocation failed.\n");
        map[lines++] = line;  // تخزين السطر في الخريطة
    }
    map[lines] = NULL;
    close(fd);
     if (!map)
    {
        ft_putstr_fd("Error\nEmpty map file\n", 2);  // إذا ما كانت الخريطة فارغة نعرض رسالة خطأ
        return (NULL);  // نرجع NULL
    }
    return (map);
}

void print_map(char **map)
{
    int i;

    if (!map)
    {
        ft_putstr_fd("Error\nMap is NULL.\n", 2);
        return;
    }

    ft_putstr_fd("Map Content:\n", 1);
    i = 0;
    while (map[i])
    {
        if (map[i])  // تأكد من أن السطر ليس NULL
            ft_putstr_fd(map[i], 1);
        else
            ft_putstr_fd("NULL line found.\n", 2);
        i++;
    }
}

void free_map(char **map)
{
    int i;

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

int rectangular(char **map)
{
    size_t i;
    size_t first_line;
    
    i = 1;
    first_line = ft_strlen(map[0]);
    if (!first_line)
        error("im here");
    
    while (map[i])
    {
        if(ft_strlen(map[i]) != first_line)
            error("Error\n Map is not rectangular\n");
        i++;
    }
    return(1);
}

void    error(char *str)
{
    ft_putstr_fd(str, 2);
    exit(EXIT_FAILURE);
}

int main(int argc, char **argv)
{
    char    **map;
   // int     i;

    if(argc != 2)
        error("Error\nToo Few Arguments\n");        
    if (!ends_with_ber(argv[1]))
        error("Error\nThe file must have a .ber extension.\n");
    map = read_map(argv[1]);
    print_map(map);
    rectangular(map);
	free_map(map);
	return (0);
    return (0);
}
