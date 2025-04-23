#include "../../include/screensaver.h"

t_aRGB	color_2_argb(int aRGB)
{
	unsigned char	a;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	a = (aRGB >> 24) & 0xFF;
	r = (aRGB >> 16) & 0xFF;
	g = (aRGB >> 8) & 0xFF;
	b = aRGB & 0xFF;
	return ((t_aRGB){.a = a, .r = r, .g = g, .b = b});
}

