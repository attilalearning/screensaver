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

