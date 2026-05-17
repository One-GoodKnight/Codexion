#include "utils.h"
#include <unistd.h>

void	ft_msleep(int time)
{
	long long	target_time;

	target_time = ft_get_time() + time * 1000;
	while (ft_get_time() < target_time)
		usleep(100);
}

void	ft_usleep(int time)
{
	long long	target_time;

	target_time = ft_get_time() + time;
	while (ft_get_time() < target_time)
		usleep(10);
}
