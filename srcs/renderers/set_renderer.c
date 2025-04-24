/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_renderer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 11:28:37 by aistok            #+#    #+#             */
/*   Updated: 2025/04/24 12:10:39 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/screensaver.h"

void	set_renderer(t_my_data *md)
{
	static int	func = 0;

	func++;
	if (func > 2)
		func = 0;
	mlx_loop_hook(md->mlx, md->rfunc[func], md);
}
