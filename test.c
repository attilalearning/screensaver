#include "mlx_linux/mlx.h"
#include "mlx_linux/mlx_int.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "libft/libft.h"

#ifndef WW
#define WW 792
#endif

#ifndef WH
#define WH 198
#endif

enum
{
	NS_PER_SECOND = 1000000000
};

enum e_exit_codes
{
	eOK,
	eMlxErr,
	eMlxWinErr
};

enum e_key_codes
{
	k_ESC = 65307,
	k_left = 65361,
	k_up = 65362,
	k_right = 65363,
	k_down = 65364,
	k_a = 97,
	k_d = 100,
	k_r = 114,
	k_s = 115,
	k_w = 119,
	k_x = 120
};

enum e_mouse_buttons
{
	m_LeftButt = 1,
	m_MiddleButt,
	m_RightButt,
	m_ScrollUp,
	m_ScrollDown
};

enum e_direction
{
	d_RANDOM,
	d_KEYBOARD
};

/*
 *	bpp - bit per pixel
 *	ll	- line length
 */
typedef struct	s_canvas
{
	void	*img;
	char	*addr;
	int		bpp;
	int		ll;
	int		endian;
	int		w;
	int		h;
}	t_canvas;

/* 
 *	complex number
 *		z = a + ib
 */
typedef struct	s_cn
{
	double	a;
	double	b;
}	t_cn;

typedef struct	s_aRGB
{
	char	a;
	char	r;
	char	g;
	char	b;
}	t_aRGB;

typedef struct	s_point
{
	double	x;
	double	y;
}	t_point;


/*
 *	ww - window width
 *	wh - window height
 *	px - point_x
 *	py - point_y
 *	pd - point direction
 *	tx - text's starting x coordinate
 *	ty - text's starting y coordinate
 */
typedef struct	s_my_data
{
	int			ww;
	int			wh;
	void		*mlx;
	void		*win;
	t_canvas	frame[2];
	int			active_frame;
	int			px;
	int			py;
	int			dirx;
	int			diry;
	int			pd;
	int			exit_code;
	int			keyb;
	int			tx;
	int			ty;
	t_canvas	c_size[2];
	int			curr_size;
}	t_my_data;


int	cleanup(t_my_data *md);


void	put_pixel(t_canvas *cdata, int x, int y, int color)
{
	char	*dst;

	dst = cdata->addr + (y * cdata->ll + x * (cdata->bpp / 8));
	*(unsigned int *)dst = color;
}

void	put_cross(t_my_data *md, int x, int y, int color)
{
	int	i;

	i = 0;
	while (i < md->ww)
		put_pixel(&md->frame[md->active_frame], i++, y, color);
	i = 0;
	while (i < md->wh)
		put_pixel(&md->frame[md->active_frame], x, i++, color);
}

int	is_control_key(int key)
{
	if ((key == k_up) || (key == k_w)
		|| (key == k_down) || (key == k_s)
		|| (key == k_right) || (key == k_d)
		|| (key == k_left) || (key == k_a))
		return (1);
	return (0);
}

int	key_handler(int key, t_my_data *md)
{
	printf("Key in Win : %d\n", key);
	md->keyb = key;
	if (is_control_key(key))
		md->pd = d_KEYBOARD;
	else
		md->pd = d_RANDOM;
	if (key == k_ESC)
		mlx_loop_end(md->mlx);
}

int	mouse_click_handler(int mbutt, int x, int y, void *md_ptr)
{
	t_my_data *md;

	md = (t_my_data *)md_ptr;
	if (mbutt == m_ScrollUp)
	{
		//..
	}
	else if (mbutt == m_ScrollDown)
	{
		//..
	}
	else if (mbutt == m_LeftButt)
		mlx_mouse_hide(md->mlx, md->win);
	else if (mbutt == m_RightButt)
		mlx_mouse_show(md->mlx, md->win);
	else if (mbutt == m_MiddleButt)
		mlx_loop_end(md->mlx);
	printf("Mouse click @ %d x %d <-- button %d\n", x, y, mbutt);
}

int	fix_if_out_of_bound(int val, int max)
{
	if (val > max)
		return (0);
	if (val < 0)
		return (max);
	return (val);
}

void	set_direction(t_my_data *md, int *dirx, int *diry)
{
	if (md->keyb == k_down || md->keyb == k_s)
		*diry = 1;
	else if (md->keyb == k_up || md->keyb == k_w)
		*diry = -1;
	else if (md->keyb == k_right || md->keyb == k_d)
		*dirx = 1;
	else if (md->keyb == k_left || md->keyb == k_a)
		*dirx = -1;
}

int	change_color(int *aRGB)
{
	static int	count = 0;
	static int	dir = 1;
	int	a;
	int	r;
	int	g;
	int	b;

	if (!(count % 100))
	{
		a = (*aRGB >> 24) & 0xFF;
		r = (*aRGB >> 16) & 0xFF;
		g = (*aRGB >> 8) & 0xFF;
		b = *aRGB & 0xFF;
		r++;
		if (r > 0xFF)
			r = 100;
		if (r < 100)
			r = 0xFF;
		*aRGB = a;
		*aRGB = (*aRGB << 8) | r;
		*aRGB = (*aRGB << 8) | g;
		*aRGB = (*aRGB << 8) | b;
		count = 0;
		if (dir == 1)
			dir = -1;
		else
			dir = 1;
	}
	count += dir;
	return (*aRGB);
}

void	make_rectangle(t_my_data *md, t_canvas *cvs, int aRGB)
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

void clock_diff(struct timespec t1, struct timespec t2, struct timespec *td)
{
    td->tv_nsec = t2.tv_nsec - t1.tv_nsec;
    td->tv_sec  = t2.tv_sec - t1.tv_sec;
    if (td->tv_sec > 0 && td->tv_nsec < 0)
    {
        td->tv_nsec += NS_PER_SECOND;
        td->tv_sec--;
    }
    else if (td->tv_sec < 0 && td->tv_nsec > 0)
    {
        td->tv_nsec -= NS_PER_SECOND;
        td->tv_sec++;
    }
}


int	put_fps(t_my_data *md, int x, int y, int color)
{
	static struct timespec	start_time;
	static struct timespec	current_time;
	static struct timespec	delta;
	static int				fps = 0;
	static char				fps_str[30];
	static int				call_count = 0;

	if (call_count == 0)
	{
		printf("Init clock!\n");
		clock_gettime(CLOCK_REALTIME, &start_time);
	}
	else
	{
		clock_gettime(CLOCK_REALTIME, &current_time);
		clock_diff(start_time, current_time, &delta);
		if (delta.tv_sec > 0)
		{
			fps = call_count;
			call_count = 0;
			sprintf(fps_str, "%d fps", fps);
			printf("elapsed %d.%.9ld graphics @ %s\n", (int)delta.tv_sec, delta.tv_nsec, fps_str);
			return (fps);
		}
	}
	mlx_string_put(md->mlx, md->win, x, y, color, fps_str);
	call_count++;
	return (0);
}

void	change_direction(t_my_data *md, int *new_dirx, int *new_diry)
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
			*new_dirx--;
	}
	while (*new_diry == last_diry)
	{
		*new_diry = random() % 3 - 1;
		if (*new_diry == 0)
			*new_diry--;
	}
	last_dirx = *new_dirx;
	last_diry = *new_diry;
}

t_aRGB	color_2_argb(int aRGB)
{
	unsigned char	a;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	a = (aRGB >> 24) & 0xFF;
	r = (aRGB >> 16) & 0xFF;
	g = (aRGB >> 8) & 0xFF;
	b = aRGB & 0xFF;
	return ((t_aRGB){.a = a, .r = r, .g = g, .b = b});
}

int	color_2_int(t_aRGB aRGB)
{
	int	color;

	color = aRGB.a;
	color = (color << 8) | aRGB.r;
	color = (color << 8) | aRGB.g;
	color = (color << 8) | aRGB.b;
	return (color);
}

int	color_add(int aRGB, t_aRGB values)
{
	t_aRGB	aRGB_vals;

	aRGB_vals = color_2_argb(aRGB);
	aRGB_vals.a += values.a;
	aRGB_vals.r += values.r;
	aRGB_vals.g += values.g;
	aRGB_vals.b += values.b;
	return (color_2_int(aRGB_vals));
}

int	render_next_frame3(t_my_data *md)
{
	static int		color = 0x00800000;
	static int		loops = 0;
	static int		max_loops = 100;

	if (md->pd == d_RANDOM)
	{
		if (loops > max_loops)
		{
			change_direction(md, &md->dirx, &md->diry);
			max_loops = random() % 100 + 1;
			loops = 0;
		}
	}
	else if (md->pd == d_KEYBOARD)
		set_direction(md, &md->dirx, &md->diry);
	md->px = fix_if_out_of_bound(md->px + md->dirx, md->ww);
	md->py = fix_if_out_of_bound(md->py + md->diry, md->wh);
	//put_cross(md, md->px, md->py, change_color(&color));
	put_pixel(&md->frame[md->active_frame], md->px, md->py, change_color(&color));
	mlx_put_image_to_window(md->mlx, md->win, md->frame[md->active_frame].img, 0, 0);
	mlx_string_put(md->mlx, md->win, md->tx, md->ty, 0x00FFFFFF, "Hit ESC to exit...");
	put_fps(md, md->tx, md->ty - 20, 0x00FFFFFF);
	loops++;
}

int	render_next_frame2(t_my_data *md)
{
	static int		color = 0x00800000;

	if (md->pd == d_RANDOM)
	{
		md->dirx = random() % 3 - 1;
		md->diry = random() % 3 - 1;
	}
	else
		set_direction(md, &md->dirx, &md->diry);
	md->px = fix_if_out_of_bound(md->px + md->dirx, md->ww);
	md->py = fix_if_out_of_bound(md->py + md->diry, md->wh);
	//put_cross(md, md->px, md->py, change_color(&color));
	put_pixel(&md->frame[md->active_frame], md->px, md->py, change_color(&color));
	mlx_put_image_to_window(md->mlx, md->win, md->frame[md->active_frame].img, 0, 0);
	mlx_string_put(md->mlx, md->win, md->tx, md->ty, 0x00FFFFFF, "Hit ESC to exit...");
	put_fps(md, md->tx, md->ty - 20, 0x00FFFFFF);
}

int	render_next_frame1(t_my_data *md)
{
	static int		color = 0x00800000;

	if (md->pd == d_RANDOM)
	{
		md->dirx = random() % 3 - 1;
		md->diry = random() % 3 - 1;
	}
	else
		set_direction(md, &md->dirx, &md->diry);
	md->px = fix_if_out_of_bound(md->px + md->dirx, md->ww);
	md->py = fix_if_out_of_bound(md->py + md->diry, md->wh);
	if (md->keyb == k_x)
	{
		md->curr_size = !md->curr_size;
		md->keyb = -1;
	}
	make_rectangle(md, &md->c_size[md->curr_size], change_color(&color));
	mlx_put_image_to_window(md->mlx, md->win, md->c_size[md->curr_size].img, md->px, md->py);
	mlx_string_put(md->mlx, md->win, md->tx, md->ty, 0x00FFFFFF, "Hit ESC to exit...");
	put_fps(md, md->tx, md->ty - 20, 0x00FFFFFF);
}

int	init(t_my_data *md)
{
	md->ww = WW;
	md->wh = WH;
	md->mlx = mlx_init();
	if (!md->mlx)
		return (md->exit_code = eMlxErr);
	md->win = mlx_new_window(md->mlx, md->ww, md->wh, "Hello");
	if (!md->win)
		return (md->exit_code = eMlxWinErr);
	mlx_key_hook(md->win, key_handler, md);
	md->frame[0].img = NULL;
	md->frame[1].img = NULL;
	md->frame[0].img = mlx_new_image(md->mlx, md->ww, md->wh);
	md->frame[0].addr = mlx_get_data_addr(md->frame[0].img, &md->frame[0].bpp, &md->frame[0].ll, &md->frame[0].endian);
	md->active_frame = 0;
	md->px = md->ww / 2;
	md->py = md->wh / 2;
	md->pd = d_RANDOM;
	md->tx = 20;
	md->ty = WH - 20;
	md->c_size[0].w = 15;
	md->c_size[0].h = 15;
	md->c_size[0].img = mlx_new_image(md->mlx, md->c_size[0].w, md->c_size[0].h);
	md->c_size[0].addr = mlx_get_data_addr(md->c_size[0].img, &md->c_size[0].bpp, &md->c_size[0].ll, &md->c_size[0].endian);
	make_rectangle(md, &md->c_size[0], 0x00FFA0A0);
	md->c_size[1].w = 300;
	md->c_size[1].h = 300;
	md->c_size[1].img = mlx_new_image(md->mlx, md->c_size[1].w, md->c_size[1].h);
	md->c_size[1].addr = mlx_get_data_addr(md->c_size[1].img, &md->c_size[1].bpp, &md->c_size[1].ll, &md->c_size[1].endian);
	make_rectangle(md, &md->c_size[1], 0x00FFA0A0);
	md->curr_size = 0;
	md->dirx = 0;
	md->diry = 0;
	return (eOK);
}

int	cleanup(t_my_data *md)
{
	if (md->frame[1].img)
		mlx_destroy_image(md->mlx, md->frame[1].img);
	if (md->frame[0].img)
		mlx_destroy_image(md->mlx, md->frame[0].img);
	if (md->c_size[0].img)
		mlx_destroy_image(md->mlx, md->c_size[0].img);
	if (md->c_size[1].img)
		mlx_destroy_image(md->mlx, md->c_size[1].img);
	if (md->win)
		mlx_destroy_window(md->mlx, md->win);
	if (md->mlx)
	{
		mlx_destroy_display(md->mlx);
		free(md->mlx);
	}
}

int	main(void)
{
	t_my_data	md;

	if (init(&md) == eOK)
	{
		//mlx_loop_hook(md.mlx, render_next_frame1, &md);
		mlx_loop_hook(md.mlx, render_next_frame2, &md);
		// mlx_loop_hook(md.mlx, render_next_frame3, &md);
		mlx_mouse_hook(md.win, mouse_click_handler, &md);
		mlx_hook(md.win, 17, 0, mlx_loop_end, md.mlx);
		mlx_loop(md.mlx);
		cleanup(&md);
	}
	return (0);
}
