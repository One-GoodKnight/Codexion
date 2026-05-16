#include "coder.h"
#include "codexion.h"
#include "dongle.h"
#include <stdlib.h>

int	init_codexion(t_codexion *codexion)
{																																																																							
	codexion->coders = init_coders(codexion);
	if (!codexion->coders)
		return (-1);
	codexion->dongles = init_dongles(codexion->args.number_of_coders);
	if (!codexion->dongles)
	{
		free(codexion->coders);
		return (-1);
	}
	get_dongle_pairs(codexion);
	return (0);
}

void	free_codexion(t_codexion *codexion)
{
	free(codexion->coders);
	free_dongles(codexion->dongles, codexion->args.number_of_coders);
}
