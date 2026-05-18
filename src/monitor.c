/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aginiaux <aginiaux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 18:29:24 by aginiaux          #+#    #+#             */
/*   Updated: 2026/05/18 18:57:33 by aginiaux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "coder.h"
#include "codexion.h"
#include "dongle.h"
#include "queue.h"
#include "utils.h"
#include <pthread.h>

static void	release_threads(t_codexion *codexion)
{
	int		i;

	i = 0;
	while (i < codexion->args.number_of_coders)
	{
		pthread_mutex_lock(&codexion->dongles[i].owner_id_lock);
		pthread_cond_broadcast(&codexion->dongles[i].owner_cond);
		pthread_mutex_unlock(&codexion->dongles[i].owner_id_lock);
		i++;
	}
}

static bool	burnout(t_codexion *codexion, t_coder *coder)
{
	bool		burnout;
	long long	burnout_time_usec;

	pthread_mutex_lock(&coder->comp_start_or_count_lock);
	burnout_time_usec = (long long)codexion->args.time_to_burnout * 1000;
	burnout = ft_get_time() - coder->last_compile_start >= burnout_time_usec;
	pthread_mutex_unlock(&coder->comp_start_or_count_lock);
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
	int		compiles_required;
	int		i;

	required = true;
	i = 0;
	while (i < codexion->args.number_of_coders)
	{
		coder = &codexion->coders[i];
		pthread_mutex_lock(&coder->comp_start_or_count_lock);
		compiles_required = codexion->args.number_of_compiles_required;
		required = coder->compile_count >= compiles_required;
		pthread_mutex_unlock(&coder->comp_start_or_count_lock);
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

static void	broadcast(long long time, t_dongle *dongle)
{
	bool	dongle_available;
	t_coder	*coder;

	pthread_mutex_lock(&dongle->owner_id_lock);
	dongle_available = (dongle->owner_id == -1);
	pthread_mutex_unlock(&dongle->owner_id_lock);
	if (!dongle_available)
		return ;
	pthread_mutex_lock(&dongle->when_available_lock);
	dongle_available = (time >= dongle->when_available);
	pthread_mutex_unlock(&dongle->when_available_lock);
	if (!dongle_available)
		return ;
	pthread_mutex_lock(&dongle->queue.lock);
	coder = q_extract(&dongle->queue);
	pthread_mutex_unlock(&dongle->queue.lock);
	if (!coder)
		return ;
	pthread_mutex_lock(&dongle->owner_id_lock);
	dongle->owner_id = coder->id;
	pthread_cond_broadcast(&dongle->owner_cond);
	pthread_mutex_unlock(&dongle->owner_id_lock);
}

void	monitor(t_codexion *codexion)
{
	int			i;
	long long	time;

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
		time = ft_get_time();
		i = 0;
		while (i < codexion->args.number_of_coders)
			broadcast(time, &codexion->dongles[i++]);
		ft_usleep(100);
	}
}
