/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_cross.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 11:28:53 by aistok            #+#    #+#             */
/*   Updated: 2025/04/24 11:35:34 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/screensaver.h"

void	put_cross(t_my_data *md, int x, int y, int color)
{
	int	i;

	i = 0;
	while (i < md->ww)
		put_pixel(&md->canvas, i++, y, color);
	i = 0;
	while (i < md->wh)
		put_pixel(&md->canvas, x, i++, color);
}
