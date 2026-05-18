/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aginiaux <aginiaux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 18:48:56 by aginiaux          #+#    #+#             */
/*   Updated: 2026/05/18 18:48:57 by aginiaux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include "args.h"
# include <pthread.h>
# include <stdbool.h>

typedef struct s_coder t_coder;
typedef struct s_dongle t_dongle;

typedef struct s_codexion
{
	long long		start_time;
	t_args			args;
	t_coder			*coders;
	t_coder			*burned_out_coder;
	t_dongle		*dongles;
	pthread_mutex_t	print_lock;
	bool			end;
	pthread_mutex_t	end_lock;
}	t_codexion;

int		init_codexion(t_codexion *codexion);
void	free_codexion(t_codexion *codexion);

#endif
