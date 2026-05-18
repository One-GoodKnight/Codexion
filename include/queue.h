/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aginiaux <aginiaux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 18:49:06 by aginiaux          #+#    #+#             */
/*   Updated: 2026/05/18 18:49:07 by aginiaux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUEUE_H
# define QUEUE_H

# include <pthread.h>

# define QUEUE_SIZE 2

typedef struct s_coder t_coder;

typedef enum	e_mode
{
	FIFO,
	EDF,
}	t_mode;

typedef struct	s_request
{
	t_coder		*coder;
	long long	value;
}	t_request;

typedef struct	s_queue
{
	t_request		requests[QUEUE_SIZE];
	int				last_i;
	int				max_i;
	t_mode			mode;
	pthread_mutex_t	lock;
}	t_queue;

int		q_init(t_queue *queue, char *mode);
void	q_insert(t_queue *queue, t_coder *coder);
t_coder	*q_extract(t_queue *queue);
void	free_q(t_queue *queue);

void	swap_requests(t_queue *queue, int one, int two);
void	heapify_last_request(t_queue *queue);
void	heapify_first_request(t_queue *queue);

#endif
