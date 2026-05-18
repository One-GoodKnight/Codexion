/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aginiaux <aginiaux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 18:49:09 by aginiaux          #+#    #+#             */
/*   Updated: 2026/05/18 18:49:09 by aginiaux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROUTINE_H
# define ROUTINE_H

# include "codexion.h"

void	start_routines(t_codexion *codexion);

bool	ended(t_codexion *codexion);
void	take_dongles(t_coder *coder);

void	compile(t_coder *coder);
void	debug(t_coder *coder);
void	refactor(t_coder *coder);

#endif
