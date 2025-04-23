#include "../../include/screensaver.h"

void	put_cross(t_my_data *md, int x, int y, int color)
{
	int	i;

	i = 0;
	while (i < md->ww)
		put_pixel(&md->canvas, i++, y, color);
	i = 0;
	while (i < md->wh)
		put_pixel(&md->canvas, x, i++, color);
}

