/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcongolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 19:19:55 by jcongolo          #+#    #+#             */
/*   Updated: 2024/10/17 19:24:48 by jcongolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	size_t	i;
	int		sign;
	int		convert;

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
	while ((unsigned char)nptr[i] >= 48 && (unsigned char)nptr[i] <= 57)
	{
		convert = (convert * 10) + ((unsigned char)nptr[i] - 48);
		i++;
	}
	return (sign * convert);
}
/*
int main()
{
	const char	string[]= "-1";
	int	conver = ft_atoi(string);
	int	conver2 = atoi(string);
	printf("Valor de %d é convertido : %d de tipo inteiro.\n", conver2, conver);
	return 0;
}
*/
