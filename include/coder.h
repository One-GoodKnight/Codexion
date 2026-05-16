#ifndef CODER_H
# define CODER_H

# include "dongle.h"
# include <pthread.h>

typedef struct s_codexion t_codexion;

typedef enum	e_state
{
	COMPILING,
	DEBUGING,
	REFACTORING
}	t_state;

typedef struct	s_coder
{
	pthread_t		thread;
	int				id;
	t_state			state;
	int				state_progress;
	t_dongle_pair	dongle_pair;
	t_codexion		*codexion;
}	t_coder;

t_coder	*init_coders(t_codexion *codexion);
void	get_dongle_pairs(t_codexion *codexion);

#endif
