#include "../../include/screensaver.h"

int	color_2_int(t_aRGB aRGB)
{
	int	color;

	color = aRGB.a;
	color = (color << 8) | aRGB.r;
	color = (color << 8) | aRGB.g;
	color = (color << 8) | aRGB.b;
	return (color);
}

