/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 11:27:21 by aistok            #+#    #+#             */
/*   Updated: 2025/04/24 11:33:47 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/screensaver.h"

void	show_error(t_my_data *md)
{
	if (md->exit_code == eMlxErr)
		printf("Error initializing mlx!\n");
	else if (md->exit_code == eMlxWinErr)
		printf("Error initializing mlx window!\n");
	else if (md->exit_code == eMlxImgErr)
		printf("Error initializing mlx image!\n");
}
