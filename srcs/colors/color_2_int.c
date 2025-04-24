/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_2_int.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 11:30:34 by aistok            #+#    #+#             */
/*   Updated: 2025/04/24 11:56:34 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/screensaver.h"

int	color_2_int(t_aRGB aRGB)
{
	int	color;

	color = aRGB.a;
	color = (color << 8) | aRGB.r;
	color = (color << 8) | aRGB.g;
	color = (color << 8) | aRGB.b;
	return (color);
}
