/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcongolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:09:01 by jcongolo          #+#    #+#             */
/*   Updated: 2024/10/16 19:32:04 by jcongolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
	{
		return (1);
	}
	else if (c >= '0' && c <= '9')
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
	char alNum;
	
	printf("Digite qualquer tipo de digito que seja AlfaNumerico: ");
	scanf("%c", &alNum);

	if (ft_isalnum(alNum))
	{
		printf("%c é Alfa Numerico. \n", alNum);
	}
	else
	{
		printf("%c nao é Alfa Numerico. \n", alNum);
	}
	return 0;
} */
