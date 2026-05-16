#include "routine.h"
#include "coder.h"
#include "codexion.h"
#include "utils.h"
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

static void	take_dongles(t_coder *coder)
{
	t_dongle	*first_dongle;
	t_dongle	*second_dungle;

	if (coder->id % 2 == 0)
	{
		first_dongle = coder->dongle_pair.left;
		second_dungle = coder->dongle_pair.right;
	}
	else
	{
		first_dongle = coder->dongle_pair.right;
		second_dungle = coder->dongle_pair.left;
	}
	pthread_mutex_lock(&first_dongle->lock);
	ft_printf(coder, TAKING_DONGLE);
	pthread_mutex_lock(&second_dungle->lock);
	ft_printf(coder, TAKING_DONGLE);
}

static void	*routine(void *arg)
{
	t_coder	*coder;

	coder = (t_coder *)arg;
	take_dongles(coder);
	compile(coder);
	debug(coder);
	refactor(coder);
	return (NULL);
}

int	start_routines(t_codexion *codexion)
{
	int		i;
	int		j;

	i = 0;
	while (i < codexion->args.number_of_coders)
	{
		if (pthread_create(&codexion->coders[i].thread, NULL, &routine, &codexion->coders[i]) != 0)
			break ;
		i++;
	}
	j = 0;
	while (j < i)
	{
		if (pthread_join(codexion->coders[j].thread, NULL) != 0)
			fprintf(stderr, "Failed to join thread of coder %d\n", j);
		j++;
	}
	return (0);
}
