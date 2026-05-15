#ifndef CODER_H
# define CODER_H

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
	int			id;
	t_state		state;
	int			state_progress;
	pthread_t	thread;
	t_codexion	*codexion;
}	t_coder;

t_coder	**init_coders(t_codexion *codexion, int number_of_coders);
void	free_coders(t_coder **coders);

#endif
