#include "../../include/screensaver.h"

int	mouse_click_handler(int mbutt, int x, int y, void *md_ptr)
{
	t_my_data *md;

	md = (t_my_data *)md_ptr;
	if (mbutt == m_ScrollUp)
	{
	}
	else if (mbutt == m_ScrollDown)
	{
	}
	else if (mbutt == m_LeftButt)
		mlx_mouse_hide(md->mlx, md->win);
	else if (mbutt == m_RightButt)
		mlx_mouse_show(md->mlx, md->win);
	else if (mbutt == m_MiddleButt)
		mlx_loop_end(md->mlx);
	printf("Mouse click @ %d x %d <-- button %d\n", x, y, mbutt);
	return (0);
}

