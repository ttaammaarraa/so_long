#include "so_long.h"

int	init_window(t_window *win)
{
	int	height;
	int	width;

	if (!win || !win->map || !win->map[0])
		return (1);
	width = ft_strlen(win->map[0]) - 1;
	height = 0;
	while (win->map[height])
		height++;
	win->mlx = mlx_init();
	if (!win->mlx)
		return (1);
	win->mlx_win = mlx_new_window(win->mlx, width * 60, height * 60, "so_long");
	if (!win->mlx_win)
	{
		mlx_destroy_display(win->mlx);
		free(win->mlx);
		return (1);
	}
	return (0);
}

int	close_window(t_window *win)
{
	mlx_destroy_image(win->mlx, win->img.floor);
	mlx_destroy_image(win->mlx,win->img.wall);
	mlx_destroy_image(win->mlx, win->img.player);
	mlx_destroy_image(win->mlx, win->img.collectable);
	mlx_destroy_image(win->mlx, win->img.exit);
	mlx_destroy_window(win->mlx, win->mlx_win);
	mlx_destroy_display(win->mlx);
	free(win->mlx);
	free_map(win->map);
	exit(EXIT_SUCCESS);
	return (0);
}

void	load_images(t_window *win)
{
	win->img.player = mlx_xpm_file_to_image(win->mlx, "./textures/player.xpm", &win->img_width, &win->img_height);
	win->img.wall = mlx_xpm_file_to_image(win->mlx, "./textures/wall.xpm", &win->img_width, &win->img_height);
	win->img.floor = mlx_xpm_file_to_image(win->mlx, "./textures/floor.xpm", &win->img_width, &win->img_height);
	win->img.collectable = mlx_xpm_file_to_image(win->mlx, "./textures/collectable.xpm", &win->img_width, &win->img_height);
	win->img.exit = mlx_xpm_file_to_image(win->mlx, "./textures/exit.xpm", &win->img_width, &win->img_height);

	if (!win->img.player || !win->img.wall || !win->img.floor || !win->img.collectable || !win->img.exit)
	{
		error("Error\nFailed to load one or more images.\n");
	}
}

void render_map(t_window *win)
{
    int x;
    int y;
    void *img;
    
    img = NULL; 
    if (!win->map)
    {
        free_map(win->map);
        error("Error\nMap is not initialized.\n");
    }
    y = 0;
    while (win->map[y])
    {
        x = 0;
        while (win->map[y][x])
        {
            if (win->map[y][x] == '\n')
                break;
            img = win->img.floor;
            if (win->map[y][x] == '1')
                img = win->img.wall;
            else if (win->map[y][x] == 'C')
                img = win->img.collectable;
            else if (win->map[y][x] == 'E')
            {
                if (win->collectibles == 0)
                    img = win->img.exit;
                else
                    img = win->img.floor;
            }
            mlx_put_image_to_window(win->mlx, win->mlx_win, img, x * 60, y * 60);
            x++;
        }
        y++;
    }
    mlx_put_image_to_window(win->mlx, win->mlx_win, win->img.player,
                            win->player_x * 60, win->player_y * 60);
}


void move_player(t_window *win, int new_x, int new_y)
{
    if (win->map[new_y][new_x] == '1')
        return;
    if (win->map[new_y][new_x] == 'C')
    {
        win->collectibles--;
        win->map[new_y][new_x] = '0';
    }
    if (win->map[new_y][new_x] == 'E')
    {

        if (win->collectibles == 0)
        {
            close_window(win);
            return;
        }
    }
    win->player_x = new_x;
    win->player_y = new_y;
    win->moves++;
    printf("Moves: %d\n", win->moves);
    render_map(win);
}

int count_collectibles(char **map)
{
    int y, x, count;

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
void find_player_position(t_window *win)
{
    int y;
    int x;

    y = 0;
    while (win->map[y])
    {
        x = 0;
        while (win->map[y][x])
        {
            if (win->map[y][x] == 'P')
            {
                win->player_x = x;
                win->player_y = y;
				win->map[y][x] = '0';
                return;
            }
            x++;
        }
        y++;
    }
}



int	key_hook(int keycode, t_window *win)
{
	if (keycode == XK_Escape || keycode == XK_q)
		close_window(win);
    else if (keycode == XK_w || keycode == XK_Up)
        move_player(win, win->player_x, win->player_y - 1);
    else if (keycode == XK_s || keycode == XK_Down)
        move_player(win, win->player_x, win->player_y + 1);
    else if (keycode == XK_a || keycode == XK_Left)
        move_player(win, win->player_x - 1, win->player_y);
    else if (keycode == XK_d || keycode == XK_Right)
        move_player(win, win->player_x + 1, win->player_y);
    return (0);
}

int	key_hook1(int keycode, t_window *win)
{
	(void)win;
	printf("Hello from key_hook!\n%d\n", keycode);
	return (0);
}
