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
}

int	init_codexion(t_codexion *codexion)
{
	if (pthread_mutex_init(&codexion->print_lock, NULL) != 0)
		return (-1);
	codexion->coders = init_coders(codexion);
	if (!codexion->coders)
	{
		if (pthread_mutex_destroy(&codexion->print_lock) != 0)
			fprintf(stderr, "Failed to destroy mutex print of codexion.\n");
		return (-1);
	}
	codexion->dongles = init_dongles(codexion->args.number_of_coders);
	if (!codexion->dongles)
	{
		if (pthread_mutex_destroy(&codexion->print_lock) != 0)
			fprintf(stderr, "Failed to destroy mutex print of codexion.\n");
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
	if (pthread_mutex_destroy(&codexion->print_lock) != 0)
		fprintf(stderr, "Failed to destroy mutex print of codexion.\n");
	free_coders(codexion->coders, codexion->args.number_of_coders);
	free_dongles(codexion->dongles, codexion->args.number_of_coders);
}
