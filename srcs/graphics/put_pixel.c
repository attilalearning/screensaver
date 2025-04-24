/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 11:29:18 by aistok            #+#    #+#             */
/*   Updated: 2025/04/24 11:55:20 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/screensaver.h"

void	put_pixel(t_canvas *cdata, int x, int y, int color)
{
	char	*dst;

	dst = cdata->addr + (y * cdata->ll + x * (cdata->bpp / 8));
	*(unsigned int *)dst = color;
}
