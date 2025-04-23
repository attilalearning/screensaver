#include "../include/screensaver.h"

static int	init_graphics(t_my_data *md, int window_w, int window_h)
{
	md->ww = window_w;
	md->wh = window_h;
	md->mlx = mlx_init();
	if (!md->mlx)
		return (md->exit_code = eMlxErr);
	md->win = mlx_new_window(md->mlx, md->ww, md->wh, "Hello");
	if (!md->win)
		return (md->exit_code = eMlxWinErr);
	return (eOK);
}

void	make_rectangle(t_canvas *cvs, int aRGB)
{
	int	i;

	i = 0;
	while (i < cvs->w)
	{
		put_pixel(cvs, i, 0, aRGB);
		put_pixel(cvs, i, cvs->h - 1, aRGB);
		put_pixel(cvs, 0, i, aRGB);
		put_pixel(cvs, cvs->w - 1, i, aRGB);
		i++;
	}
}

static int	init_rectangle(t_my_data *md, int i, int iw, int ih)
{
	t_canvas	*cvs;

	cvs = &md->c_size[i];
	cvs->w = iw;
	cvs->h = ih;
	cvs->img = mlx_new_image(md->mlx, cvs->w, cvs->h);
	if (!cvs->img)
		return (md->exit_code = eMlxImgErr);
	cvs->addr = mlx_get_data_addr(cvs->img, \
		&cvs->bpp, &cvs->ll, &cvs->endian);
	make_rectangle(cvs, 0x00FFA0A0);
	return (md->exit_code = eOK);
}

int	init(t_my_data *md)
{
	if (init_graphics(md, WW, WH) != eOK)
		return (md->exit_code);
	md->canvas.img = mlx_new_image(md->mlx, md->ww, md->wh);
	md->canvas.addr = mlx_get_data_addr(md->canvas.img, &md->canvas.bpp, &md->canvas.ll, &md->canvas.endian);
	md->px = md->ww / 2;
	md->py = md->wh / 2;
	md->pd = d_RANDOM;
	md->tx = 20;
	md->ty = WH - 20;
	if (init_rectangle(md, 0, 15, 15) != eOK
		|| init_rectangle(md, 1, 300, 300) != eOK)
		return (md->exit_code);
	md->curr_size = 0;
	md->dirx = 0;
	md->diry = 0;
	md->rfunc[0] = render_one_pixel_at_a_time;
	md->rfunc[1] = render_small_or_large_frame_at_a_time;
	md->rfunc[2] = render_one_pixel_at_a_time_in_a_direction_loop;
	return (eOK);
}

