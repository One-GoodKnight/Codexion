#ifndef UTILS_H
# define UTILS_H

# include "coder.h"

int			ft_atoi(const char *nptr, int *err);
long long	ft_get_time(void);
void		ft_printf(t_coder *coder, t_state state);
void		ft_msleep(int time);
void		ft_usleep(int time);

#endif
