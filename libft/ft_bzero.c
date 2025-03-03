/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcongolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 20:22:16 by jcongolo          #+#    #+#             */
/*   Updated: 2024/09/30 21:24:21 by jcongolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*str;
	size_t			i;

	str = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		str[i] = 0;
		i++;
	}
}

/*
int main()
{	
	char	org[50];
	ft_bzero(org, 10);
	printf("Valor preenchido na variavel ORG é: %s\n", org);
	return 0;

	char	org[50];
	size_t	bytes;

	printf("Quantas memoria necessitas a locar com zero ou seja nulo?\n");
	scanf("%zu", &bytes);
	ft_bzero(org, bytes);
	printf("Valor preenchido na variavel ORG é: %s\n", org);
	return 0;
}
*/
