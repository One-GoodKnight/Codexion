#include "dongle.h"
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

t_dongle	*init_dongles(int nb_dongles)
{
	t_dongle	*dongles;
	int	i;

	dongles = malloc(sizeof(t_dongle) * nb_dongles);
	if (!dongles)
		return (NULL);
	memset(dongles, 0, sizeof(t_dongle) * nb_dongles);
	i = 0;
	while (i < nb_dongles)
	{
		if (pthread_mutex_init(&dongles[i].lock, NULL) != 0)
		{
			free_dongles(dongles, nb_dongles);
			return (NULL);
		}
		i++;
	}
	return (dongles);
}

void	free_dongles(t_dongle *dongles, int nb_dongles)
{
	int	i;

	i = 0;
	while (i < nb_dongles)
	{
		if (pthread_mutex_destroy(&dongles[i].lock) != 0)
			fprintf(stderr, "Failed to destroy mutex of dongle %d.\n", i);
		i++;
	}
	free(dongles);
}
