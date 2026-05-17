#include "coder.h"
#include "codexion.h"
#include "dongle.h"
#include "utils.h"
#include <pthread.h>

static void	release_threads(t_codexion *codexion)
{
	int		i;

	i = 0;
	while (i < codexion->args.number_of_coders)
	{
		pthread_mutex_lock(&codexion->dongles[i].cd_lock);
		pthread_cond_broadcast(&codexion->dongles[i].cd_cond);
		pthread_mutex_unlock(&codexion->dongles[i].cd_lock);
		i++;
	}
}

static bool	burnout(t_codexion *codexion, t_coder *coder)
{
	bool	burnout;

	pthread_mutex_lock(&coder->compile_time_or_count_lock);
	burnout = (ft_get_time() - coder->last_compile_time) / 1000 >= codexion->args.time_to_burnout;
	pthread_mutex_unlock(&coder->compile_time_or_count_lock);
	if (burnout)
	{
		pthread_mutex_lock(&codexion->end_lock);
		codexion->end = true;
		pthread_mutex_unlock(&codexion->end_lock);
		release_threads(codexion);
		codexion->burned_out_coder = coder;
		return (true);
	}
	return (false);
}

static void	broadcast_if_needed(long long time, t_dongle *dongle)
{
	bool		broadcast;

	broadcast = false;
	pthread_mutex_lock(&dongle->when_available_lock);
	if (time >= dongle->when_available)
		broadcast = true;
	pthread_mutex_unlock(&dongle->when_available_lock);
	if (broadcast)
	{
		pthread_mutex_lock(&dongle->cd_lock);
		pthread_cond_broadcast(&dongle->cd_cond);
		pthread_mutex_unlock(&dongle->cd_lock);
	}
}

static bool	compiles_required(t_codexion *codexion)
{
	t_coder	*coder;
	bool	required;
	int		i;

	i = 0;
	while (i < codexion->args.number_of_coders)
	{
		coder = &codexion->coders[i];
		pthread_mutex_lock(&coder->compile_time_or_count_lock);
		required = coder->compile_count >= codexion->args.number_of_compiles_required;
		pthread_mutex_unlock(&coder->compile_time_or_count_lock);
		if (!required)
			return (false);
		i++;
	}
	return (true);
}

void	monitor(t_codexion *codexion)
{
	int			i;

	while (1)
	{
		i = 0;
		while (i < codexion->args.number_of_coders)
		{
			if (burnout(codexion, &codexion->coders[i]))
				return ;
			if (compiles_required(codexion))
			{
				pthread_mutex_lock(&codexion->end_lock);
				codexion->end = true;
				pthread_mutex_unlock(&codexion->end_lock);
				release_threads(codexion);
				return ;
			}
			broadcast_if_needed(ft_get_time(), &codexion->dongles[i]);
			i++;
		}
		ft_usleep(100);
	}
}
