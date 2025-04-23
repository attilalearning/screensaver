#include "../../include/screensaver.h"

int	key_handler(int key, t_my_data *md)
{
	printf("Key in Win : %d\n", key);
	md->keyb = key;
	if (is_control_key(key))
		md->pd = d_KEYBOARD;
	else
		md->pd = d_RANDOM;
	if (key == k_q)
		set_renderer(md);
	if (key == k_ESC)
		mlx_loop_end(md->mlx);
	return (0);
}

