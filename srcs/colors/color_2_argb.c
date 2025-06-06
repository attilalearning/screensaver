/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_2_argb.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 11:30:17 by aistok            #+#    #+#             */
/*   Updated: 2025/04/24 11:56:19 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/screensaver.h"

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
