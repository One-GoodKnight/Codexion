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
