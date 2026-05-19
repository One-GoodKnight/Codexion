/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aginiaux <aginiaux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 18:29:36 by aginiaux          #+#    #+#             */
/*   Updated: 2026/05/19 03:34:08 by aginiaux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "args.h"
#include "coder.h"
#include "codexion.h"
#include "routine.h"
#include <pthread.h>
#include <unistd.h>

int	main(int argc, char **argv)
{
	t_codexion	codexion;

	if (parse_args(&codexion.args, argc, argv) == -1)
		return (-1);
	if (codexion.args.number_of_compiles_required == 0)
		return (0);
	if (init_codexion(&codexion) == -1)
		return (1);
	start_routines(&codexion);
	free_codexion(&codexion);
	return (0);
}
