/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aginiaux <aginiaux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 18:30:23 by aginiaux          #+#    #+#             */
/*   Updated: 2026/05/18 22:37:33 by aginiaux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include "queue.h"
#include "utils.h"
#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int	q_init(t_queue *queue, char *mode)
{
	if (pthread_mutex_init(&queue->lock, NULL) != 0)
		return (-1);
	memset(queue->requests, 0, sizeof(t_request) * QUEUE_SIZE);
	queue->last_i = -1;
	queue->max_i = QUEUE_SIZE - 1;
	if (strcmp(mode, "fifo") == 0)
		queue->mode = FIFO;
	else
		queue->mode = EDF;
	return (0);
}

void	q_insert(t_queue *queue, t_coder *coder)
{
	long long	value;
	long long	burnout_time;
	long long	deadline;

	if (queue->last_i >= queue->max_i)
	{
		fprintf(stderr, "Can't insert coder in a full queue.\n");
		return ;
	}
	queue->last_i++;
	queue->requests[queue->last_i].coder = coder;
	if (queue->mode == FIFO)
		value = ft_get_time();
	else
	{
		burnout_time = coder->codexion->args.time_to_burnout;
		deadline = coder->last_compile_start + burnout_time;
		value = deadline;
	}
	queue->requests[queue->last_i].value = value;
	heapify_last_request(queue);
}

t_coder	*q_extract(t_queue *queue)
{
	t_request	*min_request;

	if (queue->last_i == -1)
		return (NULL);
	swap_requests(queue, 0, queue->last_i);
	min_request = &queue->requests[queue->last_i];
	queue->last_i--;
	heapify_first_request(queue);
	return (min_request->coder);
}

void	free_q(t_queue *queue)
{
	if (pthread_mutex_destroy(&queue->lock) != 0)
		fprintf(stderr, "Failed to destroy mutex of queue.\n");
}
