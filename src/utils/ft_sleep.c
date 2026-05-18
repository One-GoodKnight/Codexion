/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sleep.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aginiaux <aginiaux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 18:30:12 by aginiaux          #+#    #+#             */
/*   Updated: 2026/05/18 18:30:17 by aginiaux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include "utils.h"
#include <pthread.h>
#include <unistd.h>

void	ft_msleep(t_codexion *codexion, int time)
{
	bool		end;
	long long	target_time;

	target_time = ft_get_time() + (long long)time * 1000;
	while (ft_get_time() < target_time)
	{
		pthread_mutex_lock(&codexion->end_lock);
		end = codexion->end;
		pthread_mutex_unlock(&codexion->end_lock);
		if (end)
			return ;
		usleep(100);
	}
}

void	ft_usleep(int time)
{
	long long	target_time;

	target_time = ft_get_time() + (long long)time;
	while (ft_get_time() < target_time)
		usleep(10);
}
