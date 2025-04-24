/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_control_key.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 11:29:32 by aistok            #+#    #+#             */
/*   Updated: 2025/04/24 12:14:27 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/screensaver.h"

int	is_control_key(int key)
{
	if ((key == k_up) || (key == k_w)
		|| (key == k_down) || (key == k_s)
		|| (key == k_right) || (key == k_d)
		|| (key == k_left) || (key == k_a))
		return (1);
	return (0);
}
