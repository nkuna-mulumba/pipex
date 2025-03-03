/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcongolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 17:08:08 by jcongolo          #+#    #+#             */
/*   Updated: 2024/09/19 17:40:01 by jcongolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
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
	char	caract_imp;

	printf("Introduza qualquer tipo de caracter que seja imprimivel: ");
	scanf("%c", &caract_imp);

	if (ft_isprint(caract_imp))
	{
		printf("O caractere (digito) %c é imprimivel. \n", caract_imp);
	}
	else
	{
		printf("O caracter (digito) %c nao é imprimivel. \n", caract_imp);
	}
} */
