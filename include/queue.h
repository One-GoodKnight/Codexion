#ifndef QUEUE_H
# define QUEUE_H

# include "coder.h"

typedef struct	s_queue
{
	t_coder	**coders;
	int		last_i;
	int		max_i;
}	t_queue;

int		q_init(t_queue *queue, int size);
void	q_insert(t_queue *queue, t_coder *coder);
void	q_extract(t_queue *queue);
void	q_decrease(t_coder *coder);

#endif
