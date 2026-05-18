#include "coder.h"
#include "codexion.h"
#include "dongle.h"
#include "queue.h"
#include "routine.h"
#include "utils.h"

static bool	my_dongle(t_coder *coder, t_dongle *dongle)
{
	bool	mine;

	mine = coder->id == dongle->owner_id;
	return (mine);
}

static void	take_dongle(t_coder *coder, t_dongle *dongle)
{
	pthread_mutex_lock(&dongle->queue.lock);
	q_insert(&dongle->queue, coder);
	pthread_mutex_unlock(&dongle->queue.lock);
	pthread_mutex_lock(&dongle->owner_id_lock);
	while (!(my_dongle(coder, dongle)))
	{
		if (ended(coder->codexion))
		{
			pthread_mutex_unlock(&dongle->owner_id_lock);
			return ;
		}
		pthread_cond_wait(&dongle->owner_cond, &dongle->owner_id_lock);
	}
	pthread_mutex_unlock(&dongle->owner_id_lock);
	ft_printf(coder, TAKING_DONGLE);
}

void	take_dongles(t_coder *coder)
{
	take_dongle(coder, coder->dongle_pair.first);
	if (ended(coder->codexion))
		return ;
	take_dongle(coder, coder->dongle_pair.second);
	if (ended(coder->codexion))
		return ;
}
