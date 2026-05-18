/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aginiaux <aginiaux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 18:49:11 by aginiaux          #+#    #+#             */
/*   Updated: 2026/05/18 18:49:11 by aginiaux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "coder.h"

int			ft_atoi(const char *nptr, int *err);
long long	ft_get_time(void);
void		ft_memcpy(void *dest, void *src, size_t n);
void		ft_printf(t_coder *coder, t_state state);

void		ft_msleep(t_codexion *codexion, int time);
void		ft_usleep(int time);

#endif
