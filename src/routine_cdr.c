#include "coder.h"
#include "codexion.h"
#include "utils.h"

void	compile(t_coder *coder)
{
	t_codexion	*codexion;

	codexion = coder->codexion;
	ft_printf(coder, COMPILING);
	ft_msleep(codexion->args.time_to_compile);
	pthread_mutex_lock(&coder->dongle_pair.left->when_available_lock);
	pthread_mutex_lock(&coder->dongle_pair.right->when_available_lock);
	coder->dongle_pair.left->when_available = codexion->args.dongle_cooldown * 1000;
	coder->dongle_pair.right->when_available = codexion->args.dongle_cooldown * 1000;
	pthread_mutex_unlock(&coder->dongle_pair.left->when_available_lock);
	pthread_mutex_unlock(&coder->dongle_pair.right->when_available_lock);
	pthread_mutex_unlock(&coder->dongle_pair.left->lock);
	pthread_mutex_unlock(&coder->dongle_pair.right->lock);
	pthread_mutex_lock(&coder->compile_count_lock);
	coder->compile_count++;
	pthread_mutex_unlock(&coder->compile_count_lock);
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
