#include "../include/screensaver.h"

int	main(void)
{
	t_my_data	md;

	if (init(&md) == eOK)
	{
		mlx_key_hook(md.win, key_handler, &md);
		mlx_loop_hook(md.mlx, render_one_pixel_at_a_time, &md);
		mlx_mouse_hook(md.win, mouse_click_handler, &md);
		mlx_hook(md.win, 16, 0, mlx_loop_end, md.mlx);
		mlx_loop(md.mlx);
	}
	else
		show_error(&md);
	cleanup(&md);
	return (-1);
}
