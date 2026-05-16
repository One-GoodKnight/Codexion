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
			free_dongles(dongles, i - 1);
				return (NULL);
		}
		if (pthread_cond_init(&dongles[i].cond, NULL) != 0)
		{
			if (pthread_mutex_destroy(&dongles[i].lock) != 0)
				fprintf(stderr, "Failed to destroy mutex of dongle %d.\n", i);
			free_dongles(dongles, i - 1);
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
		if (pthread_cond_destroy(&dongles[i].cond) != 0)
			fprintf(stderr, "Failed to destroy cond of dongle %d.\n", i);
		i++;
	}
	free(dongles);
}
