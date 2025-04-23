#include "../../include/screensaver.h"
#include <time.h>

enum	e_time
{
	start_t = 0,
	curr_t,
	delta_t
};

/*
 * Source:
 * https://stackoverflow.com/questions/74402102/in-struct-timespec-tv-sec-and-tv-nsec-express-the-same-time-in-seconds-and-in-na/74404612#74404612
 */
void clock_diff(struct timespec t1, struct timespec t2, \
	struct timespec *td)
{
	static int	NS_PER_SECOND = 1000000000;

	td->tv_nsec = t2.tv_nsec - t1.tv_nsec;
	td->tv_sec  = t2.tv_sec - t1.tv_sec;
	if (td->tv_sec > 0 && td->tv_nsec < 0)
	{
		td->tv_nsec += NS_PER_SECOND;
		td->tv_sec--;
	}
	else if (td->tv_sec < 0 && td->tv_nsec > 0)
	{
		td->tv_nsec -= NS_PER_SECOND;
		td->tv_sec++;
	}
}

int	put_fps(t_my_data *md, int x, int y, int color)
{
	static struct timespec	t[3];
	static int				fps = 0;
	static char				fps_str[30];
	static int				call_count = 0;

	if (call_count == 0)
		clock_gettime(CLOCK_REALTIME, &t[start_t]);
	else
	{
		clock_gettime(CLOCK_REALTIME, &t[curr_t]);
		clock_diff(t[start_t], t[curr_t], &t[delta_t]);
		if (t[delta_t].tv_sec > 0)
		{
			fps = call_count;
			call_count = 0;
			sprintf(fps_str, "%d fps", fps);
			return (fps);
		}
	}
	mlx_string_put(md->mlx, md->win, x, y, color, fps_str);
	call_count++;
	return (0);
}

