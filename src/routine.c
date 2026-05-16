#include "coder.h"
#include "codexion.h"
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

static void	*routine(void *arg)
{
	t_coder	*coder;

	coder = (t_coder *)arg;
	printf("%d\n", coder->codexion->args.number_of_coders);
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
