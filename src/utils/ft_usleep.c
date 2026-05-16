#include <unistd.h>

void	ft_usleep(int time)
{
	long long	target_time;
	long long	time_passed;

	target_time = time * 1000;
	time_passed = 0;
	while (time_passed < target_time)
	{
		time_passed += 100;
		usleep(100);
	}
}
