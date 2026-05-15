#ifndef CODEXION_H
# define CODEXION_H

# include "args.h"

typedef struct s_coder t_coder;
typedef struct s_dongle t_dongle;

typedef struct s_codexion
{
	t_args		args;
	t_coder		**coders;
	t_dongle	**dongles;
}	t_codexion;

int		init_codexion(t_codexion *codexion);
void	free_codexion(t_codexion *codexion);

#endif
