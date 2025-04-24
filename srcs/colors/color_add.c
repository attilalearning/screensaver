/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_add.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 11:30:42 by aistok            #+#    #+#             */
/*   Updated: 2025/04/24 12:06:13 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/screensaver.h"

int	color_add(int aRGB, t_aRGB values)
{
	t_aRGB	argb_vals;

	argb_vals = color_2_argb(aRGB);
	argb_vals.a += values.a;
	argb_vals.r += values.r;
	argb_vals.g += values.g;
	argb_vals.b += values.b;
	return (color_2_int(argb_vals));
}
