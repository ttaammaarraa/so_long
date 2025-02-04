#include "so_long.h"

int	init_window(t_window *win)
{
	win->mlx = mlx_init();
	if(!win->mlx)
		return (1);
	win->mlx_win = mlx_new_window(win->mlx, 900, 800, "so_long");
	if(!win->mlx_win)
	{
	
		free(win->mlx);
		return (1);
	}
	return (0);
}
void close_window(t_window *win)
{
	mlx_destroy_window(win->mlx, win->mlx_win);
	mlx_destroy_display(win->mlx);
	free(win->mlx);
	exit(EXIT_SUCCESS);
	
}
void	key_hook(int keycode, t_window *win)
{
	if (keycode == XK_Escape || keycode == XK_q)
		close_window(win);
}
int		key_hook1(int keycode, t_window *win)
{
	(void)win;
	printf("Hello from key_hook!\n%d\n", keycode);
	return (0);
}


