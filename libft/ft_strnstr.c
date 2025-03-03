/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcongolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 21:07:35 by jcongolo          #+#    #+#             */
/*   Updated: 2024/10/17 19:12:10 by jcongolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t		i;
	const char	*b;
	const char	*l;
	size_t		j;

	if (*little == '\0')
		return ((char *)big);
	i = 0;
	while (i < len && big[i] != '\0')
	{
		b = (char *)&big[i];
		l = little;
		j = 0;
		while ((i + j < len) && (b[j] != '\0') && (l[j] != '\0')
			&& (b[j] == l[j]))
		{
			j++;
			if (l[j] == '\0')
				return ((char *)&big[i]);
		}
		i++;
	}
	return (NULL);
}
/*
int main()
{
	const char	um[]= "Mulumba wa Tshipamba";
	const char	dois[]= "mba";
	char	*ocorrencia = ft_strnstr(um, dois, 8);
	if (ocorrencia != NULL)
	{
		printf("Foi encontrada ocorrencia de %s em %s segundo tamanho 
		especificado.\n", dois, um);
	}
	else
	{
		printf("Ocorrencia de %s, nao encontrado em %s, segundo o tamanho 
		especificado.\n", dois, um);
	}
	return (0);
}
*/
