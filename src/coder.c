#include "coder.h"
#include "codexion.h"
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

void	free_coders(t_coder *coders);

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
		coders[i].id = i;
		coders[i].codexion = codexion;
		i++;
	}
	return (coders);
}

void	get_dongle_pairs(t_codexion *codexion)
{
	int	i;
	int	max_i;

	max_i = codexion->args.number_of_coders - 1;
	codexion->coders[0].dongle_pair.left = &codexion->dongles[0];
	codexion->coders[0].dongle_pair.right = &codexion->dongles[max_i];
	i = 1;
	while (i <= max_i)
	{
		codexion->coders[i].dongle_pair.left = &codexion->dongles[i];
		codexion->coders[i].dongle_pair.right = &codexion->dongles[i - 1];
		i++;
	}
}
