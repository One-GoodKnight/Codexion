#include "queue.h"
#include <string.h>
#include <stdlib.h>

void	q_init(t_queue *queue)
{
	memset(queue, 0, sizeof(t_queue));
}

int		q_insert(t_queue *queue, t_coder *coder)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (-1);
	memset(node, 0, sizeof(t_node));
	node->value = coder;
	if (!queue->last)
	{
		queue->min = node;
		queue->last = node;
	}
	queue
	queue->l
}

void	q_extract(t_queue *queue)
{

}

void	q_decrease(t_node *node)
{

}
