/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ended.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aginiaux <aginiaux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 18:40:08 by aginiaux          #+#    #+#             */
/*   Updated: 2026/05/18 18:40:09 by aginiaux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

bool	ended(t_codexion *codexion)
{
	bool	end;

	pthread_mutex_lock(&codexion->end_lock);
	end = codexion->end;
	pthread_mutex_unlock(&codexion->end_lock);
	return (end);
}
