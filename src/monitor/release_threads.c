/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   release_threads.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aginiaux <aginiaux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 19:45:29 by aginiaux          #+#    #+#             */
/*   Updated: 2026/05/18 19:45:30 by aginiaux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include "dongle.h"

void	release_threads(t_codexion *codexion)
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
