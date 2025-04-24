/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 11:30:10 by aistok            #+#    #+#             */
/*   Updated: 2025/04/24 11:58:27 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/screensaver.h"

int	change_color(int *aRGB)
{
	static int				count = 0;
	static int				dir = 1;
	static unsigned char	max = 0xFE;
	static unsigned char	min = 0x64;
	t_aRGB					values;

	if (!(count % 100))
	{
		values = color_2_argb(*aRGB);
		if (values.r >= max)
			dir = -1;
		else if (values.r <= min)
			dir = 1;
		values.r += dir;
		*aRGB = color_2_int(values);
		count = 0;
	}
	count++;
	return (*aRGB);
}
