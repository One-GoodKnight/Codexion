#include "args.h"

int	main(int argc, char **argv)
{
	t_args	args;

	if (parse_args(&args, argc, argv) == -1)
		return (1);

	display_args(&args);

	return (0);
}
