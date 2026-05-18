/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   q_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aginiaux <aginiaux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 18:30:26 by aginiaux          #+#    #+#             */
/*   Updated: 2026/05/19 00:02:02 by aginiaux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

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
	int	tie_breaker_id_parent;
	int	tie_breaker_id_child;

	i = queue->last_i;
	while (i != 0)
	{
		i_parent = (i - 1) / 2;
		if (queue->requests[i_parent].value < queue->requests[i].value)
			return ;
		if (queue->requests[i_parent].value == queue->requests[i].value)
		{
			tie_breaker_id_parent = queue->requests[i_parent].coder->id;
			tie_breaker_id_child = queue->requests[i].coder->id;
			if (tie_breaker_id_parent < tie_breaker_id_child)
				return ;
			swap_requests(queue, i_parent, i);
			return ;
		}
		swap_requests(queue, i_parent, i);
		i = i_parent;
	}
}

void	heapify_first_request(t_queue *q)
{
	int			i;
	int			i_left;
	int			i_right;
	int			i_min;
	t_request	*reqs;

	reqs = q->requests;
	i = 0;
	while (i < q->last_i)
	{
		i_left = i * 2 + 1;
		i_right = i * 2 + 2;
		i_min = i;
		if (i_left <= q->last_i && reqs[i_left].value < reqs[i_min].value)
			i_min = i_left;
		if (i_right <= q->last_i && reqs[i_right].value < reqs[i_min].value)
			i_min = i_right;
		if (i == i_min)
			break ;
		swap_requests(q, i_min, i);
		i = i_min;
	}
}
