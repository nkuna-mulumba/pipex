/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcongolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:59:23 by jcongolo          #+#    #+#             */
/*   Updated: 2024/09/30 21:46:02 by jcongolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if ((c >= 'a') && (c <= 'z'))
	{
		return (c - 32);
	}
	else
	{
		return (c);
	}
}
/*
int main()
{
	char	menuscula[50] = "Hola";
	char	mauscula[50];
	int		i = 0;

	while (menuscula[i] != '\0')
	{
		mauscula[i] = ft_toupper(menuscula[i]);
		i++;
	}
	mauscula[i] = '\0';
	printf("Menuscula: %s é convertido para Mauscula: %s\n",
	menuscula, mauscula);
	return 0;
}
*/
