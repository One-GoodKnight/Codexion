#include "coder.h"
#include "codexion.h"
#include "dongle.h"
#include "utils.h"

static bool	burnout(t_codexion *codexion, t_coder *coder)
{
	bool	burnout;
	int		i;

	pthread_mutex_lock(&coder->lock);
	burnout = (ft_get_time() - coder->last_compile_time) / 1000 >= codexion->args.time_to_burnout;
	pthread_mutex_unlock(&coder->lock);
	if (burnout)
	{
		pthread_mutex_lock(&codexion->end_lock);
		codexion->end = true;
		pthread_mutex_unlock(&codexion->end_lock);
		ft_printf(coder, BURNOUT);
		i = 0;
		while (i < codexion->args.number_of_coders)
		{
			pthread_cond_broadcast(&codexion->dongles[i].cd_cond);
			i++;
		}
		return (true);
	}
	return (false);
}

void	monitor(t_codexion *codexion)
{
	long long	time;
	int			i;
	t_coder		*coder;
	t_dongle	*dongle;

	while (codexion->end != true)
	{
		time = ft_get_time();
		i = 0;
		while (i < codexion->args.number_of_coders)
		{
			coder = &codexion->coders[i];
			if (burnout(codexion, coder))
				return ;
			dongle = &codexion->dongles[i];
			pthread_mutex_lock(&dongle->when_available_lock);
			if (dongle->when_available < time)
				pthread_cond_broadcast(&dongle->cd_cond);
			pthread_mutex_unlock(&dongle->when_available_lock);
			i++;
		}
		ft_usleep(10);
	}
}
