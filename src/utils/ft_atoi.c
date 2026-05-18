/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aginiaux <aginiaux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 18:30:01 by aginiaux          #+#    #+#             */
/*   Updated: 2026/05/18 18:30:02 by aginiaux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

static int	set_err(int *err)
{
	*err = -1;
	return (0);
}

int	ft_atoi(const char *nptr, int *err)
{
	long long	res;
	int			i;
	int			raw_digit;

	*err = 0;
	if (!ft_isdigit(nptr[0]))
		return (set_err(err));
	res = 0;
	i = 0;
	while (nptr[i])
	{
		if (!ft_isdigit(nptr[i]))
			return (set_err(err));
		raw_digit = nptr[i] - '0';
		if (res * 10 + raw_digit > INT_MAX)
			return (set_err(err));
		res = res * 10 + raw_digit;
		i++;
	}
	return (res);
}
