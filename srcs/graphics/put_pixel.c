#include "../../include/screensaver.h"

void	put_pixel(t_canvas *cdata, int x, int y, int color)
{
	char	*dst;

	dst = cdata->addr + (y * cdata->ll + x * (cdata->bpp / 8));
	*(unsigned int *)dst = color;
}

