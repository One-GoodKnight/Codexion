#ifndef QUEUE_H
# define QUEUE_H

# include "coder.h"

typedef enum	e_mode
{
	FIFO,
	EDF,
}	t_mode;

typedef struct	s_request
{
	t_coder		*coder;
	long long	value;
}	t_request;

typedef struct	s_queue
{
	t_request	*requests;
	int			last_i;
	int			max_i;
	t_mode		mode;
}	t_queue;

int		q_init(t_queue *queue, int size, char *mode);
void	q_insert(t_queue *queue, t_coder *coder);
t_coder	*q_extract(t_queue *queue);
void	q_decrease(t_coder *coder);

#endif
