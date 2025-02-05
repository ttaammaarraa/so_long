#include "so_long.h"

int	init_window(t_window *win)
{
	win->mlx = mlx_init();
	if (!win->mlx)
		return (1);
	win->mlx_win = mlx_new_window(win->mlx, 1920, 1080, "so_long");
	if (!win->mlx_win)
	{
		free(win->mlx);
		return (1);
	}
	return (0);
}

int	close_window(t_window *win)
{
	mlx_destroy_window(win->mlx, win->mlx_win);
	mlx_destroy_display(win->mlx);
	free(win->mlx);
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

void	render_map(t_window *win)
{
	int	x, y;

	if (!win->map)
	{
		error("Error\nMap is not initialized.\n");
		return;
	}
	y = 0;
	while (win->map[y])
	{
		x = 0;
		while (win->map[y][x])
		{
			void *img = NULL;
			if (win->map[y][x] == '1')
			{
				printf("heeheheheheh\n");
				img = win->img.wall;
			}
		 	else if (win->map[x][y] == '0')
			{
				printf("hii\n");
				img = win->img.floor;
			}
			else if (win->map[y][x] == 'P')
			{
				printf("hii\n");
				img = win->img.player;
			}
			else if (win->map[y][x] == 'C')
			{
				printf("hirri\n");
				img = win->img.collectable;
			}
			else if (win->map[y][x] == 'E')
			{
				printf("hiiii\n");
				img = win->img.exit;
			}
			if (img)
				mlx_put_image_to_window(win->mlx, win->mlx_win, img, x * 120, y * 120);  // ✅ تأكد من أن الصورة ليست NULL قبل وضعها في النافذة
			else
				error("Error\nInvalid image detected.\n");

			x++;
		}
		y++;
	}
}


int	key_hook(int keycode, t_window *win)
{
	if (keycode == XK_Escape || keycode == XK_q)
		close_window(win);
	return (0);
}
int	key_hook1(int keycode, t_window *win)
{
	(void)win;
	printf("Hello from key_hook!\n%d\n", keycode);
	return (0);
}
