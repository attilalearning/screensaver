/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 11:29:41 by aistok            #+#    #+#             */
/*   Updated: 2025/04/24 12:20:24 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/screensaver.h"

int	key_handler(int key, t_my_data *md)
{
	md->keyb = key;
	if (is_control_key(key))
		md->pd = d_KEYBOARD;
	else
		md->pd = d_RANDOM;
	if (key == k_q)
		set_renderer(md);
	if (key == k_ESC)
		mlx_loop_end(md->mlx);
	return (0);
}
