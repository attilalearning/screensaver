#ifndef SCREENSAVER_H
# define SCREENSAVER_H

# include "../lib/mlx_linux/mlx.h"
# include "../lib/mlx_linux/mlx_int.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "../lib/libft/libft.h"

# ifndef WW
#  define WW 792
# endif

# ifndef WH
#  define WH 198
# endif

enum e_exit_codes
{
	eOK,
	eMlxErr,
	eMlxWinErr,
	eMlxImgErr
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
	k_q = 113,
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

typedef struct	s_aRGB
{
	unsigned char	a;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}	t_aRGB;

typedef struct	s_point
{
	double	x;
	double	y;
}	t_point;

typedef int(*render_func)(void *md);

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
	t_canvas	canvas;
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
	render_func		rfunc[3];
}	t_my_data;


/* init.c */
int	    init(t_my_data *md);
void	  make_rectangle(t_canvas *cvs, int aRGB);

/* cleanup.c */
int	    cleanup(t_my_data *md);

/* show_error.c */
void	  show_error(t_my_data *md);

/* colors dir */
int	    change_color(int *aRGB);
t_aRGB	color_2_argb(int aRGB);
int	    color_2_int(t_aRGB aRGB);
int	    color_add(int aRGB, t_aRGB values);

/* controls dir */
int	    is_control_key(int key);
int	    key_handler(int key, t_my_data *md);
int	    mouse_click_handler(int mbutt, int x, int y, void *md_ptr);
void	  set_key_dir(t_my_data *md, int *dirx, int *diry);

/* graphics dir */
void	  put_cross(t_my_data *md, int x, int y, int color);
int	    put_fps(t_my_data *md, int x, int y, int color);
void	  put_pixel(t_canvas *cdata, int x, int y, int color);

/* renderers dir */
int	    fix_if_out_of_bound(int val, int max);
int	    render_one_pixel_at_a_time(void *md_ptr);
int	    render_one_pixel_at_a_time_in_a_direction_loop(void *md_ptr);
int	    render_small_or_large_frame_at_a_time(void *md_ptr);
void	  set_renderer(t_my_data *md);

#endif
