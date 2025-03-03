/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcongolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:24:21 by jcongolo          #+#    #+#             */
/*   Updated: 2025/01/16 15:24:44 by jcongolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
//Convert Alpa to Integre com long
long	ft_atol(const char *nptr)
{
	size_t	i;
	int		sign;
	long	convert;

	i = 0;
	while (((unsigned char)nptr[i] >= 9 && (unsigned char)nptr[i] <= 13)
		|| ((unsigned char)nptr[i] == 32))
		i++;
	sign = 1;
	if (((unsigned char)nptr[i] == 43) || ((unsigned char)nptr[i] == 45))
	{
		if ((unsigned char)nptr[i] == 45)
			sign = -1;
		i++;
	}
	convert = 0;
	while (ft_isdigit((unsigned char)nptr[i]))
	{
		convert = (convert * 10) + ((unsigned char)nptr[i] - 48);
		i++;
	}
	return (sign * convert);
}
