#include "routine.h"
#include "coder.h"
#include "codexion.h"
#include "monitor.h"
#include "utils.h"
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

static bool	ended(t_codexion *codexion)
{
	bool	end;

	pthread_mutex_lock(&codexion->end_lock);
	end = codexion->end;
	pthread_mutex_unlock(&codexion->end_lock);
	return (end);
}

static bool	dongle_available(t_dongle *dongle)
{
	bool	dongle_available;

	dongle_available = false;
	pthread_mutex_lock(&dongle->when_available_lock);
	if (ft_get_time() >= dongle->when_available)
		dongle_available = true;
	pthread_mutex_unlock(&dongle->when_available_lock);
	return (dongle_available);
}

static void	take_dongle(t_coder *coder, t_dongle *dongle)
{
	pthread_mutex_lock(&dongle->owner_lock);
	while (!dongle_available(dongle))
	{
		if (ended(coder->codexion))
			return ;
		pthread_mutex_lock(&dongle->cd_lock);
		pthread_cond_wait(&dongle->cd_cond, &dongle->cd_lock);
		pthread_mutex_unlock(&dongle->cd_lock);
	}
	ft_printf(coder, TAKING_DONGLE);
}

static void	take_dongles(t_coder *coder)
{
	take_dongle(coder, coder->dongle_pair.first);
	if (ended(coder->codexion))
	{
		pthread_mutex_unlock(&coder->dongle_pair.first->owner_lock);
		return ;
	}
	take_dongle(coder, coder->dongle_pair.second);
	if (ended(coder->codexion))
	{
		pthread_mutex_unlock(&coder->dongle_pair.first->owner_lock);
		pthread_mutex_unlock(&coder->dongle_pair.second->owner_lock);
	}
}

static void	*routine(void *arg)
{
	t_coder		*coder;
	t_codexion	*codexion;

	coder = (t_coder *)arg;
	codexion = coder->codexion;
	while (!ended(codexion))
	{
		take_dongles(coder);
		if (ended(codexion))
			return (NULL);
		compile(coder);
		if (ended(codexion))
			return (NULL);
		debug(coder);
		if (ended(codexion))
			return (NULL);
		refactor(coder);
	}
	return (NULL);
}

static void	single_coder_edge_case(t_coder *coder)
{
	ft_printf(coder, TAKING_DONGLE);
	ft_msleep(coder->codexion->args.time_to_burnout);
	ft_printf(coder, BURNOUT);
}

void	start_routines(t_codexion *codexion)
{
	int		i;
	int		j;

	if (codexion->args.number_of_coders == 1)
		return (single_coder_edge_case(&codexion->coders[0]));
	i = 0;
	while (i < codexion->args.number_of_coders)
	{
		if (pthread_create(&codexion->coders[i].thread, NULL, &routine, &codexion->coders[i]) != 0)
			break ;
		i++;
	}
	monitor(codexion);
	j = 0;
	while (j < i)
	{
		if (pthread_join(codexion->coders[j].thread, NULL) != 0)
			fprintf(stderr, "Failed to join thread of coder %d\n", j);
		j++;
	}
	if (codexion->burned_out_coder)
		ft_printf(codexion->burned_out_coder, BURNOUT);
}
