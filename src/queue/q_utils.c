#include "queue.h"
#include "utils.h"

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

void	swap_requests(t_queue *queue, int one, int two)
{
	t_request	temp;

	ft_memcpy(&temp, &queue->requests[one], sizeof(t_request));
	ft_memcpy(&queue->requests[one], &queue->requests[two], sizeof(t_request));
	ft_memcpy(&queue->requests[two], &temp, sizeof(t_request));
}
