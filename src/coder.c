#include "coder.h"
#include "codexion.h"
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

void	get_dongle_pairs(t_codexion *codexion)
{
	int	i;
	int	max_i;

	max_i = codexion->args.number_of_coders - 1;
	codexion->coders[0]->dongle_pair.left = codexion->dongles[0];
	codexion->coders[0]->dongle_pair.right = codexion->dongles[max_i];
	i = 1;
	while (i <= max_i)
	{
		codexion->coders[i]->dongle_pair.left = codexion->dongles[i];
		codexion->coders[i]->dongle_pair.right = codexion->dongles[i - 1];
		i++;
	}
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
