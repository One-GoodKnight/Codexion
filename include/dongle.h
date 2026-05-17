#ifndef DONGLE_H
# define DONGLE_H

# include <pthread.h>
# include <stdbool.h>

typedef struct s_dongle
{
	pthread_mutex_t	owner_lock;
	pthread_cond_t	cd_cond;
	pthread_mutex_t	cond_lock;
	long long		when_available;
	pthread_mutex_t	when_available_lock;
}	t_dongle;

typedef struct s_dongle_pair
{
	t_dongle	*left;
	t_dongle	*right;
	t_dongle	*first;
	t_dongle	*second;
}	t_dongle_pair;

t_dongle	*init_dongles(int number_of_dongles);
void		free_dongles(t_dongle *dongles, int nb_dongles);

#endif
