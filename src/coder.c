#include "coder.h"
#include "codexion.h"
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

t_coder	*init_coders(t_codexion *codexion)
{
	t_coder	*coders;
	int	nb_coders;
	int	i;

	nb_coders = codexion->args.number_of_coders;
	coders = malloc(sizeof(t_coder) * nb_coders);
	if (!coders)
		return (NULL);
	memset(coders, 0, sizeof(t_coder) * nb_coders);
	i = 0;
	while (i < nb_coders)
	{
		if (pthread_mutex_init(&coders[i].compile_count_lock, NULL) != 0)
		{
			free_coders(coders, nb_coders);
			return (NULL);
		}
		coders[i].id = i;
		coders[i].codexion = codexion;
		i++;
	}
	return (coders);
}

void	free_coders(t_coder *coders, int nb_coders)
{
	int	i;

	i = 0;
	while (i < nb_coders)
	{
		if (pthread_mutex_destroy(&coders[i].compile_count_lock) != 0)
			fprintf(stderr, "Failed to destroy compile count mutex of coder %d.\n", i);
		i++;
	}
	free(coders);
}
