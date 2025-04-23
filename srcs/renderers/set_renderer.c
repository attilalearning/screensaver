#include "../../include/screensaver.h"

void	set_renderer(t_my_data *md)
{
	static int	func = 0;

	func++;
	if (func > 2)
		func = 0;
	mlx_loop_hook(md->mlx, md->rfunc[func], md);
}

