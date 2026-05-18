#include "codexion.h"
#include "queue.h"
#include "utils.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int	q_init(t_queue *queue, int size, char *mode)
{
	queue->requests = malloc(sizeof(t_request) * size);
	if (!queue->requests)
		return (-1);
	memset(queue, 0, sizeof(t_request) * size);
	queue->last_i = -1;
	queue->max_i = size - 1;
	if (strcmp(mode, "fifo"))
		queue->mode = FIFO;
	else
		queue->mode = EDF;
	return (0);
}

void	q_insert(t_queue *queue, t_coder *coder)
{
	long long	value;
	if (queue->last_i == queue->max_i)
	{
		fprintf(stderr, "Can't insert coder in a full queue.");
		return ;
	}
	queue->last_i++;
	queue->requests[queue->last_i].coder = coder;
	if (queue->mode == FIFO)
		value = ft_get_time();
	else
		value = coder->last_compile_start + coder->codexion->args.time_to_burnout;
	queue->requests[queue->last_i].value = value;
	heapify_last_element(queue);
}

t_coder	*q_extract(t_queue *queue)
{
	t_request	*request;
	if (queue->last_i == -1)
		return (NULL);
	swap_root_tail(queue);
	request = &queue->requests[queue->last_i];
	queue->last_i--;
	return (request->coder);
}
