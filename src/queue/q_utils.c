#include "queue.h"

void	heapify_last_request(t_queue *queue)
{
	t_request	*parent;
	int	i;

	i = queue->last_i;
	while (i != 0)
	{
		parent = &queue->requests[(i - 1) / 2];
		if (parent->value > queue->requests[i].value)

	}
}

void	heapify_first_request(t_queue *queue)
{
}

void	swap_root_tail(t_queue *queue)
{
	t_request	temp;
	t_request	*root;
	t_request	*tail;

	if (queue->last_i == -1)
		return ;
	root = &queue->requests[0];
	tail = &queue->requests[queue->last_i];
	temp.coder = root->coder;
	temp.value = root->value;
	root->coder = tail->coder;
	root->value = tail->value;
	tail->coder = temp.coder;
	tail->value = temp.value;
}
