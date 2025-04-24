/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_small_or_large_frame_at_a_time.c            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 11:28:24 by aistok            #+#    #+#             */
/*   Updated: 2025/04/24 12:17:50 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/screensaver.h"

static void	set_random_dir(t_my_data *md)
{
	md->dirx = random() % 3 - 1;
	md->diry = random() % 3 - 1;
}

static	void	draw_and_update(t_my_data *md, int *color)
{
	make_rectangle(&md->c_size[md->curr_size], \
		change_color(color));
	mlx_put_image_to_window(md->mlx, md->win, \
		md->c_size[md->curr_size].img, md->px, md->py);
}

int	render_small_or_large_frame_at_a_time(void *md_ptr)
{
	static int	color = 0x00800000;
	t_my_data	*md;

	md = (t_my_data *)md_ptr;
	if (md->pd == d_RANDOM)
		set_random_dir(md);
	else
		set_key_dir(md, &md->dirx, &md->diry);
	md->px = fix_if_out_of_bound(md->px + md->dirx, md->ww);
	md->py = fix_if_out_of_bound(md->py + md->diry, md->wh);
	if (md->keyb == k_x)
	{
		md->curr_size = !md->curr_size;
		md->keyb = -1;
	}
	if (md->pd == d_RANDOM)
		draw_and_update(md, &color);
	mlx_string_put(md->mlx, md->win, md->tx, md->ty, 0x00FFFFFF, \
		"Hit ESC to exit...");
	put_fps(md, md->tx, md->ty - 20, 0x00FFFFFF);
	return (0);
}
