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

