#include "../../include/screensaver.h"

void	set_key_dir(t_my_data *md, int *dirx, int *diry)
{
	if (md->keyb == k_down || md->keyb == k_s)
		*diry = 1;
	else if (md->keyb == k_up || md->keyb == k_w)
		*diry = -1;
	else if (md->keyb == k_right || md->keyb == k_d)
		*dirx = 1;
	else if (md->keyb == k_left || md->keyb == k_a)
		*dirx = -1;
}

