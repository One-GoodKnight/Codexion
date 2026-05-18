#ifndef DONGLE_H
# define DONGLE_H

# include "queue.h"
# include <pthread.h>
# include <stdbool.h>

typedef struct s_dongle
{
	pthread_cond_t	owner_cond;
	int				owner_id;
	pthread_mutex_t	owner_id_lock;
	long long		when_available;
	pthread_mutex_t	when_available_lock;
	t_queue			queue;
}	t_dongle;

typedef struct s_dongle_pair
{
	t_dongle	*left;
	t_dongle	*right;
	t_dongle	*first;
	t_dongle	*second;
}	t_dongle_pair;

t_dongle	*init_dongles(int nb_dongles, char *q_mode);
void		free_dongles(t_dongle *dongles, int nb_dongles);

#endif
