#include "dongle.h"
#include "queue.h"
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static int	init_cond(t_dongle *dongle)
{
	if (pthread_cond_init(&dongle->cd_cond, NULL) != 0)
	{
		if (pthread_mutex_destroy(&dongle->owner_lock) != 0)
			fprintf(stderr, "Failed to destroy owner mutex of dongle.\n");
		if (pthread_mutex_destroy(&dongle->cd_lock) != 0)
			fprintf(stderr, "Failed to destroy cond mutex of dongle.\n");
		if (pthread_mutex_destroy(&dongle->when_available_lock) != 0)
			fprintf(stderr, "Failed to destroy when avalaible mutex of dongle.\n");
		return (-1);
	}
	return (0);
}

static int	init_mutex_cond(t_dongle *dongle)
{
	if (pthread_mutex_init(&dongle->owner_lock, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&dongle->cd_lock, NULL) != 0)
	{
		if (pthread_mutex_destroy(&dongle->owner_lock) != 0)
			fprintf(stderr, "Failed to destroy owner mutex of dongle.\n");
		return (-1);
	}
	if (pthread_mutex_init(&dongle->when_available_lock, NULL) != 0)
	{
		if (pthread_mutex_destroy(&dongle->cd_lock) != 0)
			fprintf(stderr, "Failed to destroy cond mutex of dongle.\n");
		if (pthread_mutex_destroy(&dongle->owner_lock) != 0)
			fprintf(stderr, "Failed to destroy owner mutex of dongle.\n");
		return (-1);
	}
	if (init_cond(dongle) == -1)
		return (-1);
	return (0);
}

t_dongle	*init_dongles(int nb_dongles, char *q_mode)
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
		if (init_mutex_cond(&dongles[i]) == -1)
			free_dongles(dongles, i - 1);
		q_init(&dongles[i].queue, q_mode);
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
		if (pthread_mutex_destroy(&dongles[i].owner_lock) != 0)
			fprintf(stderr, "Failed to destroy owner mutex of dongle %d.\n", i);
		if (pthread_mutex_destroy(&dongles[i].cd_lock) != 0)
			fprintf(stderr, "Failed to destroy cd mutex of dongle %d.\n", i);
		if (pthread_cond_destroy(&dongles[i].cd_cond) != 0)
			fprintf(stderr, "Failed to destroy cond of dongle %d.\n", i);
		i++;
	}
	free(dongles);
}
