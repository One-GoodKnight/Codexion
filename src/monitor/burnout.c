/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burnout.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aginiaux <aginiaux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 19:45:22 by aginiaux          #+#    #+#             */
/*   Updated: 2026/05/18 20:25:46 by aginiaux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "coder.h"
#include "codexion.h"
#include "utils.h"

bool	burnout(t_codexion *codexion, t_coder *coder)
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
