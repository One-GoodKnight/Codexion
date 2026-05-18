#include "queue.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int	q_init(t_queue *queue, int size)
{
	queue->coders = malloc(sizeof(t_coder *) * size);
	if (!queue->coders)
		return (-1);
	memset(queue, 0, sizeof(t_queue));
	queue->last_i = -1;
	queue->max_i = size - 1;
	return (0);
}

void	q_insert(t_queue *queue, t_coder *coder)
{
	if (queue->last_i == queue->max_i)
	{
		fprintf(stderr, "Can't insert coder in a full queue.");
		return ;
	}
	queue->last_i++;
	queue->coders[queue->last_i] = coder;
}

void	q_extract(t_queue *queue)
{
	
}

void	q_decrease(t_node *node)
{

}
