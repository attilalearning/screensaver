#include "../../include/screensaver.h"

static void	set_random_dir(t_my_data *md)
{
	md->dirx = random() % 3 - 1;
	md->diry = random() % 3 - 1;
}

static	void	draw_and_update(t_my_data *md, int *color)
{
	put_pixel(&md->canvas, md->px, md->py, change_color(color));
	mlx_put_image_to_window(md->mlx, md->win, md->canvas.img, 0, 0);
}

int	render_one_pixel_at_a_time(void *md_ptr)
{
	static int		color = 0x00800000;
	t_my_data		*md = (t_my_data *)md_ptr;

	if (md->pd == d_RANDOM)
		set_random_dir(md);
	else
		set_key_dir(md, &md->dirx, &md->diry);
	md->px = fix_if_out_of_bound(md->px + md->dirx, md->ww);
	md->py = fix_if_out_of_bound(md->py + md->diry, md->wh);
	if (md->pd == d_RANDOM)
		draw_and_update(md, &color);
	mlx_string_put(md->mlx, md->win, 507, 20, 0x00FFFFFF, \
		"I wrote this in C using MiniLibX from 42 Paris");
	put_fps(md, 735, 37, 0x00FFFFFF);
	mlx_string_put(md->mlx, md->win, 513, 170, 0x00FFFFFF, \
		"https://github.com/attilalearning/screensaver");
	mlx_string_put(md->mlx, md->win, 574, 190, 0x00FFFFFF, \
		"I am seeking for a new challenge :)");
	return (0);
}

