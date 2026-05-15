#include "dongle.h"
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void	free_dongles(t_dongle **dongles);

t_dongle	**init_dongles(int number_of_dongles)
{
	t_dongle	**dongles;
	int	i;

	dongles = malloc(sizeof(t_dongle *) * (number_of_dongles + 1));
	if (!dongles)
		return (NULL);
	memset(dongles, 0, sizeof(t_dongle *) * (number_of_dongles + 1));
	i = 0;
	while (i < number_of_dongles)
	{
		dongles[i] = malloc(sizeof(t_dongle));
		if (!dongles[i])
		{
			free_dongles(dongles);
			return (NULL);
		}
		if (pthread_mutex_init(&dongles[i]->lock, NULL) != 0)
		{
			free(dongles[i]);
			dongles[i] = NULL;
			free_dongles(dongles);
			return (NULL);
		}
		dongles[i]->id = i;
		i++;
	}
	return (dongles);
}

void	free_dongles(t_dongle **dongles)
{
	int	i;

	i = 0;
	while (dongles[i] != NULL)
	{
		if (pthread_mutex_destroy(&dongles[i]->lock) != 0)
			fprintf(stderr, "Failed to destroy mutex of dongle %d\n", i);
		free(dongles[i]);
		i++;
	}
	free(dongles);
}
