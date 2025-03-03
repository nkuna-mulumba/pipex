/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcongolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 13:58:57 by jcongolo          #+#    #+#             */
/*   Updated: 2024/10/17 21:01:58 by jcongolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	const unsigned char	*str;

	str = (const unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (str[i] == (unsigned char)c)
		{
			return ((void *)&str[i]);
		}
		i++;
	}
	return (NULL);
}

/*
int main()
{
	const char	nome[]= "Nkuna";
	char	*ocorrencia = ft_memchr(nome, 'u', 3);

	if (ocorrencia != NULL)
	{
		printf("Ocorrencia encontrada em %s segundo tamanho especificado.\n"
		, nome);
	}
	else
	{
		printf("Ocorrencia nao encontrada em %s segundo tamanho especificado.
		\n", nome);
	}
	return 0;
}
*/
