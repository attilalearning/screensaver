/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fix_if_out_of_bound.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 11:27:47 by aistok            #+#    #+#             */
/*   Updated: 2025/04/24 12:12:51 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/screensaver.h"

int	fix_if_out_of_bound(int val, int max)
{
	if (val > max)
		return (0);
	if (val < 0)
		return (max);
	return (val);
}
