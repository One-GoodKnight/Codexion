/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compiles_required.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aginiaux <aginiaux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 19:45:24 by aginiaux          #+#    #+#             */
/*   Updated: 2026/05/18 19:45:25 by aginiaux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "coder.h"
#include "codexion.h"

bool	compiles_required(t_codexion *codexion)
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
