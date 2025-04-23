#include "../../include/screensaver.h"

static void	draw_and_update(t_my_data *md, int *color)
{
	put_pixel(&md->canvas, md->px, md->py, change_color(color));
	mlx_put_image_to_window(md->mlx, md->win, md->canvas.img, 0, 0);
}

static void
change_direction(int *new_dirx, int *new_diry)
{
	static int	last_dirx = 0;
	static int	last_diry = 0;

	if (last_dirx == 0 && last_diry == 0)
	{
		*new_dirx = random() % 3 - 1;
		*new_diry = random() % 3 - 1;
	}
	while (*new_dirx == last_dirx)
	{
		*new_dirx = random() % 3 - 1;
		if (*new_dirx == 0)
			(*new_dirx)--;
	}
	while (*new_diry == last_diry)
	{
		*new_diry = random() % 3 - 1;
		if (*new_diry == 0)
			(*new_diry)--;
	}
	last_dirx = *new_dirx;
	last_diry = *new_diry;
}

int	render_one_pixel_at_a_time_in_a_direction_loop(void *md_ptr)
{
	static int		color = 0x00800000;
	static int		loops = 0;
	static int		max_loops = 100;
	t_my_data		*md = (t_my_data *)md_ptr;

	if (md->pd == d_RANDOM)
	{
		if (loops > max_loops)
		{
			change_direction(&md->dirx, &md->diry);
			max_loops = random() % 100 + 1;
			loops = 0;
		}
	}
	else if (md->pd == d_KEYBOARD)
		set_key_dir(md, &md->dirx, &md->diry);
	md->px = fix_if_out_of_bound(md->px + md->dirx, md->ww);
	md->py = fix_if_out_of_bound(md->py + md->diry, md->wh);
	draw_and_update(md, &color);
	mlx_string_put(md->mlx, md->win, md->tx, md->ty, 0x00FFFFFF, \
		"Hit ESC to exit...");
	put_fps(md, md->tx, md->ty - 20, 0x00FFFFFF);
	loops++;
	return (0);
}
