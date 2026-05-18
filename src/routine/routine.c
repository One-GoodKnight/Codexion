/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aginiaux <aginiaux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 18:29:16 by aginiaux          #+#    #+#             */
/*   Updated: 2026/05/18 19:20:29 by aginiaux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "routine.h"
#include "coder.h"
#include "codexion.h"
#include "monitor.h"
#include "queue.h"
#include "utils.h"
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

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
		if (ended(codexion))
			return (NULL);
	}
	return (NULL);
}

static void	single_coder_edge_case(t_coder *coder)
{
	ft_printf(coder, TAKING_DONGLE);
	ft_msleep(coder->codexion, coder->codexion->args.time_to_burnout);
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
		if (pthread_create(&codexion->coders[i].thread, NULL,
				&routine, &codexion->coders[i]) != 0)
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
