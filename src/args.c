/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aginiaux <aginiaux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 19:03:48 by aginiaux          #+#    #+#             */
/*   Updated: 2026/05/18 19:08:29 by aginiaux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "args.h"
#include <stdio.h>
#include <stddef.h>
#include <string.h>

static int	print_error(char *err_msg)
{
	fprintf(stderr, "Error parsing: %s\n", err_msg);
	return (-1);
}

static int	parse_one(t_args *args, char **argv)
{
	int	err;

	args->number_of_coders = ft_atoi(argv[1], &err);
	if (err == -1 || args->number_of_coders < 0)
		return (print_error("number_of_coders should be a positive int.\n"));
	args->time_to_burnout = ft_atoi(argv[2], &err);
	if (err == -1 || args->time_to_burnout < 0)
		return (print_error("number_of_coders should be a positive int.\n"));
	args->time_to_compile = ft_atoi(argv[3], &err);
	if (err == -1 || args->time_to_compile < 0)
		return (print_error("time_to_compile should be a positive int.\n"));
	args->time_to_debug = ft_atoi(argv[4], &err);
	if (err == -1 || args->time_to_debug < 0)
		return (print_error("time_to_debug should be a positive int.\n"));
	args->time_to_refactor = ft_atoi(argv[5], &err);
	if (err == -1 || args->time_to_refactor < 0)
		return (print_error("time_to_refactor should be a positive int.\n"));
	return (0);
}

static int	parse_two(t_args *args, char **argv)
{
	int		err;
	size_t	i;

	args->number_of_compiles_required = ft_atoi(argv[6], &err);
	if (err == -1 || args->number_of_compiles_required < 0)
		return (print_error("number_of_compiles_required should be a "
				"positive int.\n"));
	args->dongle_cooldown = ft_atoi(argv[7], &err);
	if (err == -1 || args->dongle_cooldown < 0)
		return (print_error("dongle_cooldown should be a positive int.\n"));
	i = 0;
	if (strcmp("fifo", argv[8]) == 0 || strcmp("edf", argv[8]) == 0)
	{
		while (argv[8][i])
		{
			args->scheduler[i] = argv[8][i];
			i++;
		}
		args->scheduler[i] = '\0';
	}
	else
		return (print_error("scheduler should be either 'fifo' or 'edf'.\n"));
	return (0);
}

int	parse_args(t_args *args, int argc, char **argv)
{
	if (argc != 9)
		return (print_error("invalid number of arguments.\n"));
	if (parse_one(args, argv) == -1)
		return (-1);
	if (parse_two(args, argv) == -1)
		return (-1);
	return (0);
}

// void	display_args(t_args *args)
// {
// 	printf("------------------------\n");
// 	printf("number_of_coders: %d\n", args->number_of_coders);
// 	printf("time_to_burnout: %d\n", args->time_to_burnout);
// 	printf("time_to_compile: %d\n", args->time_to_compile);
// 	printf("time_to_debug: %d\n", args->time_to_debug);
// 	printf("time_to_refactor: %d\n", args->time_to_refactor);
// 	printf("number_of_compiles_required: %d\n",
// 		args->number_of_compiles_required);
// 	printf("dongle_cooldown: %d\n", args->dongle_cooldown);
// 	printf("scheduler: %s\n", args->scheduler);
// 	printf("------------------------\n");
// }
