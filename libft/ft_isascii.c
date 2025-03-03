/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcongolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 13:05:43 by jcongolo          #+#    #+#             */
/*   Updated: 2024/09/19 14:47:39 by jcongolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

/* int main()
{
	char	caractAscii;

	printf("Digite qualquer caracter que esteja dentro da tabela ASCII: ");
	scanf("%c", &caractAscii);

	if (ft_isascii(caractAscii))
	{
		printf("O valor ASCII de %c é %d esta dentro da tabela ASCII. 
		\n", caractAscii, caractAscii);
	}
	else
	{
		printf("O valor ACSII de %c é %d nao se contra dentro da tabela ASCII. 
		\n", caractAscii, caractAscii);
	}
	return 0;
} */
