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

static void	single_coder_edge_case(t_coder *coder)
{
	ft_printf(coder, TAKING_DONGLE);
	ft_usleep(coder->codexion->args.time_to_burnout);
	ft_printf(coder, BURNOUT);
}

void	start_routines(t_codexion *codexion)
{
	int		i;
	int		j;

	if (codexion->args.number_of_coders == 1)
		return (single_coder_edge_case(&codexion->coders[0]));
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
}
