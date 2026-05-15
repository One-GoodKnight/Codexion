#include "coder.h"
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

void	free_coders(t_coder **coders);

t_coder	**init_coders(t_codexion *codexion, int number_of_coders)
{
	t_coder	**coders;
	int	i;

	coders = malloc(sizeof(t_coder *) * (number_of_coders + 1));
	if (!coders)
		return (NULL);
	memset(coders, 0, sizeof(t_coder *) * (number_of_coders + 1));
	i = 0;
	while (i < number_of_coders)
	{
		coders[i] = malloc(sizeof(t_coder));
		if (!coders[i])
		{
			free_coders(coders);
			return (NULL);
		}
		coders[i]->id = i;
		coders[i]->codexion = codexion;
		i++;
	}
	return (coders);
}

void	free_coders(t_coder **coders)
{
	int	i;

	i = 0;
	while (coders[i] != NULL)
	{
		free(coders[i]);
		i++;
	}
	free(coders);
}
