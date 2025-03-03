/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcongolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 18:21:59 by jcongolo          #+#    #+#             */
/*   Updated: 2024/09/30 21:27:05 by jcongolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*str;
	size_t			i;

	i = 0;
	str = (unsigned char *)s;
	while (i < n)
	{
		str[i] = (unsigned char) c;
		i++;
	}
	return (s);
}

/*
int main()
{

	char	org[50];
	ft_memset(org, 'X', 3);
	org[3] = '\0';
	printf("Valor iniciliazado a variavel ORG é: %s\n", org);
	return 0;

	char	org[50];
	char	caract;
	size_t bytes;

	printf("Digite valor ou caracter a ser inicializada a variavel ORG: \n");
	scanf("%c", &caract);
	printf("Digite tamanho a ser alogado na variavel ORG: \n");
	scanf("%zu", &bytes);
	ft_memset(org, caract, bytes);
	org[bytes] = '\0';
	printf("A variavel é reniciada com: %s como valor ou caractere.\n", org);
	return 0;
}
*/
