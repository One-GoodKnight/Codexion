#include "coder.h"
#include "codexion.h"
#include "utils.h"
#include <pthread.h>
#include <stdio.h>

static void	release_dongles(t_coder *coder)
{
	t_codexion	*codexion;

	codexion = coder->codexion;
	pthread_mutex_lock(&coder->dongle_pair.first->when_available_lock);
	pthread_mutex_lock(&coder->dongle_pair.second->when_available_lock);
	coder->dongle_pair.first->when_available = ft_get_time() + (long long)codexion->args.dongle_cooldown * 1000;
	coder->dongle_pair.second->when_available = ft_get_time() + (long long)codexion->args.dongle_cooldown * 1000;
	pthread_mutex_unlock(&coder->dongle_pair.second->when_available_lock);
	pthread_mutex_unlock(&coder->dongle_pair.first->when_available_lock);
	pthread_mutex_lock(&coder->dongle_pair.first->owner_id_lock);
	pthread_mutex_lock(&coder->dongle_pair.second->owner_id_lock);
	coder->dongle_pair.first->owner_id = -1;
	coder->dongle_pair.second->owner_id = -1;
	pthread_mutex_unlock(&coder->dongle_pair.second->owner_id_lock);
	pthread_mutex_unlock(&coder->dongle_pair.first->owner_id_lock);
}

void	compile(t_coder *coder)
{
	t_codexion	*codexion;

	codexion = coder->codexion;
	ft_printf(coder, COMPILING);
	pthread_mutex_lock(&coder->compile_time_or_count_lock);
	coder->last_compile_start = ft_get_time();
	pthread_mutex_unlock(&coder->compile_time_or_count_lock);
	ft_msleep(codexion, codexion->args.time_to_compile);
	release_dongles(coder);
	pthread_mutex_lock(&coder->compile_time_or_count_lock);
	coder->compile_count++;
	pthread_mutex_unlock(&coder->compile_time_or_count_lock);
}

void	debug(t_coder *coder)
{
	ft_printf(coder, DEBUGGING);
	ft_msleep(coder->codexion, coder->codexion->args.time_to_debug);
}

void	refactor(t_coder *coder)
{
	ft_printf(coder, REFACTORING);
	ft_msleep(coder->codexion, coder->codexion->args.time_to_refactor);
}
