#ifndef ARGS_H
# define ARGS_H

typedef struct s_args
{
	int		number_of_coders;
	int		time_to_burnout;
	int		time_to_compile;
	int		time_to_debug;
	int		time_to_refactor;
	int		number_of_compiles_required;
	int		dongle_cooldown;
	char	scheduler[5];
}	t_args;

int		parse_args(t_args *args, int argc, char **argv);
void	display_args(t_args *args);

#endif
