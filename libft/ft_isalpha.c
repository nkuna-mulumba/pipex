/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcongolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 12:09:58 by jcongolo          #+#    #+#             */
/*   Updated: 2024/09/18 14:28:52 by jcongolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
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
	char	caract;

	printf("Digite um caractere: ");
	scanf("%c", &caract);
	
	if(ft_isalpha(caract))
	{
		printf("%c É uma letra do alfabeto.\n", caract);
	}
	else 
	{
		printf("%c Nao é uma letra do alfabeto.\n", caract);
	}
	return 0;
}*/
