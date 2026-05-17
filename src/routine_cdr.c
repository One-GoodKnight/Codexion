#include "coder.h"
#include "codexion.h"
#include "utils.h"

void	compile(t_coder *coder)
{
	t_codexion	*codexion;

	codexion = coder->codexion;
	ft_printf(coder, COMPILING);
	pthread_mutex_lock(&coder->compile_time_or_count_lock);
	coder->last_compile_time = ft_get_time();
	pthread_mutex_unlock(&coder->compile_time_or_count_lock);
	ft_msleep(codexion->args.time_to_compile);
	pthread_mutex_lock(&coder->dongle_pair.first->when_available_lock);
	pthread_mutex_lock(&coder->dongle_pair.second->when_available_lock);
	coder->dongle_pair.first->when_available = ft_get_time() + codexion->args.dongle_cooldown * 1000;
	coder->dongle_pair.second->when_available = ft_get_time() + codexion->args.dongle_cooldown * 1000;
	pthread_mutex_unlock(&coder->dongle_pair.second->when_available_lock);
	pthread_mutex_unlock(&coder->dongle_pair.first->when_available_lock);
	pthread_mutex_unlock(&coder->dongle_pair.second->owner_lock);
	pthread_mutex_unlock(&coder->dongle_pair.first->owner_lock);
	pthread_mutex_lock(&coder->compile_time_or_count_lock);
	coder->compile_count++;
	pthread_mutex_unlock(&coder->compile_time_or_count_lock);
}

void	debug(t_coder *coder)
{
	ft_printf(coder, DEBUGGING);
	ft_msleep(coder->codexion->args.time_to_debug);
}

void	refactor(t_coder *coder)
{
	ft_printf(coder, REFACTORING);
	ft_msleep(coder->codexion->args.time_to_refactor);
}
