#ifndef QUEUE_H
# define QUEUE_H

# include "coder.h"

typedef struct	s_node
{
	t_coder	*value;
	t_coder	*parent;
	t_coder	*left;
	t_coder	*right;

}	t_node;

typedef struct	s_queue
{
	t_node	*min;
	t_node	*last;
}	t_queue;

int		q_insert(t_queue *queue, t_coder *coder);
void	q_extract(t_queue *queue);
void	q_decrease(t_node *node);

#endif
