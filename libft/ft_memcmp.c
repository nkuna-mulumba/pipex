/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcongolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:41:01 by jcongolo          #+#    #+#             */
/*   Updated: 2024/10/17 20:42:13 by jcongolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*str1;
	const unsigned char	*str2;

	str1 = (const unsigned char *)s1;
	str2 = (const unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (str1[i] != str2[i])
		{
			return (str1[i] - str2[i]);
		}
		i++;
	}
	return (0);
}
/*
int main()
{
	const char	um[]= "Nkuna";
	const char	dois[]= "Ngoya";
	int	diferencia = ft_memcmp(um, dois, 3);

	if (diferencia != 0)
	{
		printf("%s e %s, tem a diferencia de %d, segundo tamanho especificado.
		\n", um, dois, diferencia);
	}
	else
	{
		printf("%s e %s nao tem diferencia segundo tamanho epecificado.\n", um, 
		dois);
	}
	return 0;
}
*/
