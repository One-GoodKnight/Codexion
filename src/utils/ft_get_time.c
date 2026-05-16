#include <sys/time.h>
#include <stddef.h>

long long	ft_get_time(void)
{
	long long		time;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000000 + tv.tv_usec;
	return (time);
}
