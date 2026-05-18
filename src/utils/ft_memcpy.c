/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aginiaux <aginiaux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 18:30:07 by aginiaux          #+#    #+#             */
/*   Updated: 2026/05/18 18:30:08 by aginiaux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	ft_memcpy(void *dest, void *src, size_t n)
{
	unsigned char	*u_dest;
	unsigned char	*u_src;
	size_t			i;

	u_dest = (unsigned char *)dest;
	u_src = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		u_dest[i] = u_src[i];
		i++;
	}
}
