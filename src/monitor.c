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
	burnout = ft_get_time() - coder->last_compile_start >= (long long)codexion->args.time_to_burnout * 1000;
	pthread_mutex_unlock(&coder->compile_time_or_count_lock);
	if (burnout)
	{
		pthread_mutex_lock(&codexion->end_lock);
		codexion->end = true;
		pthread_mutex_unlock(&codexion->end_lock);
		codexion->burned_out_coder = coder;
		return (true);
	}
	return (false);
}

static bool	compiles_required(t_codexion *codexion)
{
	t_coder	*coder;
	bool	required;
	int		i;

	required = true;
	i = 0;
	while (i < codexion->args.number_of_coders)
	{
		coder = &codexion->coders[i];
		pthread_mutex_lock(&coder->compile_time_or_count_lock);
		required = coder->compile_count >= codexion->args.number_of_compiles_required;
		pthread_mutex_unlock(&coder->compile_time_or_count_lock);
		if (!required)
			break ;
		i++;
	}
	if (required)
	{
		pthread_mutex_lock(&codexion->end_lock);
		codexion->end = true;
		pthread_mutex_unlock(&codexion->end_lock);
	}
	return (required);
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

void	monitor(t_codexion *codexion)
{
	int			i;

	while (1)
	{
		i = 0;
		while (i < codexion->args.number_of_coders)
		{
			if (burnout(codexion, &codexion->coders[i++]))
				return (release_threads(codexion));
		}
		if (compiles_required(codexion))
				return (release_threads(codexion));
		i = 0;
		while (i < codexion->args.number_of_coders)
			broadcast_if_needed(ft_get_time(), &codexion->dongles[i++]);
		ft_usleep(100);
	}
}
