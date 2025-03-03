/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isldigit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcongolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:41:33 by jcongolo          #+#    #+#             */
/*   Updated: 2024/09/18 16:53:50 by jcongolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

/*int main()
{
	char digitoDecimal;

	printf("Digite um digito: ");
	scanf("%c", &digitoDecimal);

	if (ft_isdigit(digitoDecimal))
	{
		printf("%c é um digito decimal.\n", digitoDecimal);
	}
	else
	{
		printf("%c nao é um digito decimal.\n", digitoDecimal);
	}
	return (0);
}*/
