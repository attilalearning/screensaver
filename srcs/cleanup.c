/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 11:26:57 by aistok            #+#    #+#             */
/*   Updated: 2025/04/24 11:32:54 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/screensaver.h"

int	cleanup(t_my_data *md)
{
	if (md->canvas.img)
		mlx_destroy_image(md->mlx, md->canvas.img);
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
	return (0);
}
