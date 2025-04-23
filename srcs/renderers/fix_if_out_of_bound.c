#include "../../include/screensaver.h"

int	fix_if_out_of_bound(int val, int max)
{
	if (val > max)
		return (0);
	if (val < 0)
		return (max);
	return (val);
}

