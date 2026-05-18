/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aginiaux <aginiaux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 14:55:46 by aginiaux          #+#    #+#             */
/*   Updated: 2026/05/18 18:29:46 by aginiaux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "coder.h"
#include "codexion.h"
#include "dongle.h"
#include "utils.h"
#include <stdio.h>

static void	get_dongle_pairs(t_codexion *codexion)
{
	int	i;
	int	max_i;

	max_i = codexion->args.number_of_coders - 1;
	codexion->coders[0].dongle_pair.left = &codexion->dongles[0];
	codexion->coders[0].dongle_pair.right = &codexion->dongles[max_i];
	i = 1;
	while (i <= max_i)
	{
		codexion->coders[i].dongle_pair.left = &codexion->dongles[i];
		codexion->coders[i].dongle_pair.right = &codexion->dongles[i - 1];
		i++;
	}
	i = 0;
	while (i <= max_i)
	{
		codexion->coders[i].dongle_pair.first = codexion->coders[i].dongle_pair.right;
		codexion->coders[i].dongle_pair.second = codexion->coders[i].dongle_pair.left;
		if (codexion->coders[i].id % 2 == 0)
		{
			codexion->coders[i].dongle_pair.first = codexion->coders[i].dongle_pair.left;
			codexion->coders[i].dongle_pair.second = codexion->coders[i].dongle_pair.right;
		}
		i++;
	}
}

static int	init_mutex(t_codexion *codexion)
{
	if (pthread_mutex_init(&codexion->print_lock, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&codexion->end_lock, NULL) != 0)
	{
		if (pthread_mutex_destroy(&codexion->print_lock) != 0)
			fprintf(stderr, "Failed to destroy mutex print of codexion.\n");
		return (-1);
	}
	return (0);
}

static void	destroy_mutex(t_codexion *codexion)
{
	if (pthread_mutex_destroy(&codexion->print_lock) != 0)
		fprintf(stderr, "Failed to destroy mutex print of codexion.\n");
	if (pthread_mutex_destroy(&codexion->end_lock) != 0)
		fprintf(stderr, "Failed to destroy mutex end of codexion.\n");
}

int	init_codexion(t_codexion *codexion)
{
	codexion->burned_out_coder = NULL;
	if (init_mutex(codexion) == -1)
		return (-1);
	codexion->coders = init_coders(codexion);
	if (!codexion->coders)
	{
		destroy_mutex(codexion);
		return (-1);
	}
	codexion->dongles = init_dongles(codexion->args.number_of_coders, codexion->args.scheduler);
	if (!codexion->dongles)
	{
		destroy_mutex(codexion);
		free_coders(codexion->coders, codexion->args.number_of_coders);
		return (-1);
	}
	get_dongle_pairs(codexion);
	codexion->start_time = ft_get_time();
	codexion->end = false;
	return (0);
}

void	free_codexion(t_codexion *codexion)
{
	destroy_mutex(codexion);
	free_coders(codexion->coders, codexion->args.number_of_coders);
	free_dongles(codexion->dongles, codexion->args.number_of_coders);
}
