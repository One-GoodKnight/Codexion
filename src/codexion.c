#include "coder.h"
#include "codexion.h"
#include "dongle.h"
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>

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
		free(codexion->coders);
		return (-1);
	}
	get_dongle_pairs(codexion);
	codexion->start_time = ft_get_time();
	return (0);
}

void	free_codexion(t_codexion *codexion)
{
	if (pthread_mutex_destroy(&codexion->print_lock) != 0)
		fprintf(stderr, "Failed to destroy mutex print of codexion.\n");
	free(codexion->coders);
	free_dongles(codexion->dongles, codexion->args.number_of_coders);
}
