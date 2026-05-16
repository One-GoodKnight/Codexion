#include "utils.h"
#include "coder.h"
#include "codexion.h"
#include <stdio.h>

void	ft_printf(t_coder *coder, t_state state)
{
	long long	time;
	int			id;

	time = (ft_get_time() - coder->codexion->start_time) / 1000;
	id = coder->id + 1;
	pthread_mutex_lock(&coder->codexion->print_lock);
	if (state == TAKING_DONGLE)
		printf("%llu %d has taken a dongle\n", time, id);
	else if (state == COMPILING)
		printf("%llu %d is compiling\n", time, id);
	else if (state == DEBUGGING)
		printf("%llu %d is debugging\n", time, id);
	else if (state == REFACTORING)
		printf("%llu %d is refactoring\n", time, id);
	pthread_mutex_unlock(&coder->codexion->print_lock);
}
