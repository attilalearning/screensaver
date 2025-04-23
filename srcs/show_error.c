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

