#include "so_long.h"

int	not_ends_with_ber(const char *str)
{
	size_t	len;
	char	*dot;
	dot = ft_strrchr(str, '.');
	len = ft_strlen(str);
	if (len < 4)
		return (0);
	if (!(ft_strcmp(dot, ".ber") == 0))
		error("Error\nwqer");
	return (0);
}

char **read_map1(int fd)
{
    char    *line;
    char    **map;
    int     lines;

	map = NULL;
	lines = 0;
    line = get_next_line(fd);
    while (line)
    {
        if (line[0] == '\0')
        {
            free(line);
            break;
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
    return map;
}

char **read_map(char *filename)
{
    int fd = open(filename, O_RDONLY);
    if (fd < 0)
        error("Error\nFailed to open the file.\n");
    char **map = read_map1(fd);
    close(fd);
    return map;
}
/* char	**read_map(char *filename)
{
	int		fd;
	char	*line;
	char	**map;
	int		lines;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error("Error\nFailed to open the file.\n");
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
	close(fd);
	if (!map)
		error("Error\nEmpty map file\n");
	map[lines] = NULL;

	return (map);
} */

void	print_map(char **map)
{
	int	i;

	if (!map)
	{
		ft_putstr_fd("Error\nMap is NULL.\n", 2);
		return ;
	}
	ft_putstr_fd("Map Content:\n", 1);
	i = 0;
	while (map[i])
	{
		if (map[i])
			ft_putstr_fd(map[i], 1);
		else
			ft_putstr_fd("NULL line found.\n", 2);
		i++;
	}
}

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

void	rectangular(char **map)
{
	int		i;
	size_t	first_line;

	i = 1;
	first_line = ft_strlen(map[0]);
	if (!first_line || first_line == 1)
	{
		free_map(map);
		error("Error\ninvalid map\n");
	}
	while (map[i])
	{
		if (ft_strlen(map[i]) != first_line)
		{
			free_map(map);
			error("Error\nnot rectangular\n");
		}
		i++;
	}
	if (i < 3)
	{
		free_map(map);
		error("Error\ninvalid map\n");
	}
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
	{
		free_map(map);
		error("Error\nShould have one player in the game\n");
	}
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
	{
		free_map(map);
		error("Error\nShould have one exit in the game\n");
	}
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
	{
		free_map(map);
		error("Error\nShould have one collectable at least in the game\n");
	}
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

void validate_map_chars(char **map)
{
    int y = 0, x;
    while (map[y])
    {
        x = 0;
        while (map[y][x])
        {
            if (map[y][x] != '1' && map[y][x] != '0' &&
                map[y][x] != 'P' && map[y][x] != 'C' &&
                map[y][x] != 'E' && map[y][x] != '\n')
            {
                free_map(map);
                error("Error\nInvalid character in map.\n");
            }
            x++;
        }
        y++;
    }
}

char **copy_map(char **map)
{
    int i = 0;
    char **copy = NULL;
    while (map[i])
        i++;
    copy = malloc(sizeof(char *) * (i + 1));
    if (!copy)
        return (NULL);
    for (int j = 0; j < i; j++)
    {
        copy[j] = ft_strdup(map[j]);
        if (!copy[j])
        {
            for (int k = 0; k < j; k++)
                free(copy[k]);
            free(copy);
            return (NULL);
        }
    }
    copy[i] = NULL;
    return (copy);
}

void flood_fill(char **map, int x, int y)
{
    if (y < 0 || x < 0 || !map[y] || x >= (int)ft_strlen(map[y]))
        return;
    if (map[y][x] == '1' || map[y][x] == 'V')
        return;
    map[y][x] = 'V';
    flood_fill(map, x + 1, y);
    flood_fill(map, x - 1, y);
    flood_fill(map, x, y + 1);
    flood_fill(map, x, y - 1);
}

void check_reachability(t_window *win)
{
    char **map_copy = copy_map(win->map);
    if (!map_copy)
    {
        free_map(win->map);
        error("Error\nMemory allocation failed in check_reachability.\n");
    }
    flood_fill(map_copy, win->player_x, win->player_y);
    int y = 0, x;
    while (map_copy[y])
    {
        x = 0;
        while (map_copy[y][x])
        {
            if (map_copy[y][x] == 'C' || map_copy[y][x] == 'E')
            {
                free_map(map_copy);
                free_map(win->map); 
                error("Error\nNot all collectibles or the exit are reachable.\n");
            }
            x++;
        }
        y++;
    }
    free_map(map_copy);
}
int main(int argc, char **argv)
{
    t_window win;

	if(not_ends_with_ber(argv[1]))
    if (argc != 2)
        error("Error\nWrong number of arguments.\n");
    win.map = read_map(argv[1]);
    if (!win.map)
        error("Error\nFailed to load map.\n");
    validate_map_chars(win.map);
    rectangular(win.map);
    check_wall_1(win.map);
    is_valid_exit(win.map);
    is_valid_collectable(win.map);
    is_valid_player(win.map);
    win.collectibles = count_collectibles(win.map);
    find_player_position(&win);
    win.moves = 0;
    check_reachability(&win);
    if (init_window(&win))
    {
        free_map(win.map);
        return (1);
    }
    load_images(&win);
    render_map(&win);
    mlx_hook(win.mlx_win, 2, 1L << 0, key_hook, &win);
	mlx_hook(win.mlx_win, 17, 0, close_window, &win);
    mlx_loop(win.mlx);
    free_map(win.map);
    return (0);
}
