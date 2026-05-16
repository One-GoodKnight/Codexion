#ifndef DONGLE_H
# define DONGLE_H

# include <pthread.h>
# include <stdbool.h>

typedef struct s_dongle
{
	int				delay;
	pthread_mutex_t	lock;
}	t_dongle;

typedef struct s_dongle_pair
{
	t_dongle	*left;
	t_dongle	*right;
}	t_dongle_pair;

t_dongle	*init_dongles(int number_of_dongles);
void		free_dongles(t_dongle *dongles, int nb_dongles);

#endif
