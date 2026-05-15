#include "coder.h"
#include "codexion.h"
#include "dongle.h"

int	init_codexion(t_codexion *codexion)
{																																																																							
	codexion->coders = init_coders(codexion, codexion->args.number_of_coders);
	if (!codexion->coders)
		return (-1);
	codexion->dongles = init_dongles(codexion->args.number_of_coders);
	if (!codexion->dongles)
	{
		free_coders(codexion->coders);
		return (-1);
	}
	return (0);
}

void	free_codexion(t_codexion *codexion)
{
	free_coders(codexion->coders);
	free_dongles(codexion->dongles);
}
