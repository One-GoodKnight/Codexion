#include "coder.h"
#include "codexion.h"
#include "utils.h"

void	compile(t_coder *coder)
{
	t_codexion	*codexion;

	codexion = coder->codexion;
	ft_printf(coder, COMPILING);
	pthread_mutex_lock(&coder->lock);
	coder->last_compile_time = ft_get_time();
	pthread_mutex_unlock(&coder->lock);
	ft_msleep(codexion->args.time_to_compile);
	pthread_mutex_lock(&coder->dongle_pair.left->when_available_lock);
	pthread_mutex_lock(&coder->dongle_pair.right->when_available_lock);
	coder->dongle_pair.left->when_available = ft_get_time() + codexion->args.dongle_cooldown * 1000;
	coder->dongle_pair.right->when_available = ft_get_time() + codexion->args.dongle_cooldown * 1000;
	pthread_mutex_unlock(&coder->dongle_pair.left->when_available_lock);
	pthread_mutex_unlock(&coder->dongle_pair.right->when_available_lock);
	pthread_mutex_unlock(&coder->dongle_pair.left->lock);
	pthread_mutex_unlock(&coder->dongle_pair.right->lock);
	pthread_mutex_lock(&coder->lock);
	coder->compile_count++;
	pthread_mutex_unlock(&coder->lock);
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
