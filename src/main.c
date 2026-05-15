#include "args.h"
#include "coder.h"
#include "codexion.h"
#include "routine.h"
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

int	main(int argc, char **argv)
{
	t_codexion	codexion;

	if (parse_args(&codexion.args, argc, argv) == -1)
		return (-1);
	display_args(&codexion.args);
	if (codexion.args.number_of_coders == 0)
		return (0);
	if (init_codexion(&codexion) == -1)
		return (1);
	start_routines(&codexion);
	for (int i = 0; i < 4; i++)
	{
		printf("--------\nCoder %d:\nLeft: %d\nRight: %d\n", codexion.coders[i]->id, codexion.coders[i]->dongle_pair.left->id, codexion.coders[i]->dongle_pair.right->id);
	}
	free_codexion(&codexion);
	return (0);
}
