#include "../../include/screensaver.h"

int	change_color(int *aRGB)
{
	static int	count = 0;
	static int	dir = 1;
	unsigned char	max = 0xFE;
	unsigned char	min = 0x64;
	t_aRGB		values;

	if (!(count % 100))
	{
		count = 0;
		dir *= -1;
	}
	values = color_2_argb(*aRGB);
	values.r += dir;
	if (values.r > max)
		values.r = min;
	else if (values.r < min)
		values.r = max;
	count += dir;
	return (*aRGB = color_2_int(values));
}

