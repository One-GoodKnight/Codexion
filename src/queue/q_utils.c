/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   q_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aginiaux <aginiaux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 18:30:26 by aginiaux          #+#    #+#             */
/*   Updated: 2026/05/18 19:30:12 by aginiaux         ###   ########lyon.fr   */
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

void	heapify_first_request(t_queue *q)
{
	int	i;
	int	i_left_child;
	int	i_right_child;
	int	i_smallest_child;

	i = 0;
	while (i < q->last_i)
	{
		i_left_child = i * 2 + 1;
		if (i_left_child > q->last_i)
			return ;
		i_right_child = i * 2 + 2;
		if (q->requests[i_left_child].value <= q->requests[i_right_child].value)
			i_smallest_child = i_left_child;
		else
			i_smallest_child = i_right_child;
		swap_requests(q, i_smallest_child, i);
		i = i_smallest_child;
	}
}
