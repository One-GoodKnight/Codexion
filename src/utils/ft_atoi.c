#include <limits.h>

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

static void	init_vars(int *err, long long *res, int *sign, int *i)
{
	*err = 0;
	*res = 0;
	*i = 0;
	*sign = 1;
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
	int			sign;
	int			raw_digit;

	init_vars(err, &res, &sign, &i);
	while (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
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
	return (res * sign);
}
