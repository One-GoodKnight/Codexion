#ifndef CODER_H
# define CODER_H

# include "dongle.h"
# include <pthread.h>

typedef struct s_codexion t_codexion;

typedef enum	e_state
{
	TAKING_DONGLE,
	COMPILING,
	DEBUGGING,
	REFACTORING,
	BURNOUT,
}	t_state;

typedef struct	s_coder
{
	pthread_t		thread;
	int				id;
	t_dongle_pair	dongle_pair;
	long long		last_compile_time;
	int				compile_count;
	pthread_mutex_t	lock;
	t_codexion		*codexion;
}	t_coder;

t_coder	*init_coders(t_codexion *codexion);
void	free_coders(t_coder *coders, int nb_coders);

#endif
