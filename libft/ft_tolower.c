/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcongolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 18:05:49 by jcongolo          #+#    #+#             */
/*   Updated: 2024/09/25 18:22:48 by jcongolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if ((c >= 'A') && (c <= 'Z'))
	{
		return (c + 32);
	}
	else
	{
		return (c);
	}
}

/*
int main()
{
	char	mauscula[50] = "NKUNA";
	char	menuscula[50];
	int		i = 0;

	while (mauscula[i] != '\0')
	{
		menuscula[i] = ft_tolower(mauscula[i]);
		i++;
	}
	menuscula[i] = '\0';
	printf("Caracteres maiuscula: %s é convertido para caracteres menuscula: 
	%s.\n", mauscula, menuscula);
	return 0;
}
*/
