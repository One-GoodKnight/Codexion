#include "codexion.h"
#include "dongle.h"
#include "utils.h"

void	monitor(t_codexion *codexion)
{
	long long	time;
	int			i;
	t_dongle	*dongle;

	while (codexion->end != true)
	{
		time = ft_get_time();
		i = 0;
		while (i < codexion->args.number_of_coders)
		{
			dongle = &codexion->dongles[i];
			if (dongle->when_available < time)
				pthread_cond_broadcast(&dongle->cond);
			i++;
		}
		ft_usleep(10);
	}
}
