#include "queue.h"
#include "utils.h"

void	swap_requests(t_queue *queue, int one, int two)
{
	t_request	temp;

	ft_memcpy(&temp, &queue->requests[one], sizeof(t_request));
	ft_memcpy(&queue->requests[one], &queue->requests[two], sizeof(t_request));
	ft_memcpy(&queue->requests[two], &temp, sizeof(t_request));
}

void	heapify_last_request(t_queue *queue)
{
	int	i;
	int	i_parent;

	i = queue->last_i;
	while (i != 0)
	{
		i_parent = (i - 1) / 2;
		if (queue->requests[i_parent].value <= queue->requests[i].value)
			return ;
		swap_requests(queue, i_parent, i);
		i = i_parent;
	}
}

void	heapify_first_request(t_queue *queue)
{

}
