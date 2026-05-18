/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aginiaux <aginiaux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 18:29:24 by aginiaux          #+#    #+#             */
/*   Updated: 2026/05/18 20:53:34 by aginiaux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "monitor.h"
#include "coder.h"
#include "codexion.h"
#include "dongle.h"
#include "queue.h"
#include "utils.h"

static bool	dongle_available(long long time, t_dongle *dongle)
{
	bool	dongle_available;

	pthread_mutex_lock(&dongle->owner_id_lock);
	dongle_available = (dongle->owner_id == -1);
	pthread_mutex_unlock(&dongle->owner_id_lock);
	if (!dongle_available)
		return (false);
	pthread_mutex_lock(&dongle->when_available_lock);
	dongle_available = (time >= dongle->when_available);
	pthread_mutex_unlock(&dongle->when_available_lock);
	if (!dongle_available)
		return (false);
	return (true);
}

static t_coder	*retrieve_coder_in_q(t_dongle *dongle)
{
	t_coder	*coder;

	pthread_mutex_lock(&dongle->queue.lock);
	coder = q_extract(&dongle->queue);
	pthread_mutex_unlock(&dongle->queue.lock);
	if (!coder)
		return (NULL);
	return (coder);
}

static void	broadcast(long long time, t_dongle *dongle)
{
	t_coder	*coder;

	if (!dongle_available(time, dongle))
		return ;
	coder = retrieve_coder_in_q(dongle);
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
