#include "../../include/screensaver.h"

int	color_add(int aRGB, t_aRGB values)
{
	t_aRGB	aRGB_vals;

	aRGB_vals = color_2_argb(aRGB);
	aRGB_vals.a += values.a;
	aRGB_vals.r += values.r;
	aRGB_vals.g += values.g;
	aRGB_vals.b += values.b;
	return (color_2_int(aRGB_vals));
}

