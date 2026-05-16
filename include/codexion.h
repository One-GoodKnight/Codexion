#ifndef CODEXION_H
# define CODEXION_H

# include "args.h"
# include <pthread.h>

typedef struct s_coder t_coder;
typedef struct s_dongle t_dongle;

typedef struct s_codexion
{
	long long		start_time;
	t_args			args;
	t_coder			*coders;
	t_dongle		*dongles;
	pthread_mutex_t	print_lock;
}	t_codexion;

int		init_codexion(t_codexion *codexion);
void	free_codexion(t_codexion *codexion);

#endif
