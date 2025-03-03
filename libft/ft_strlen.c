/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcongolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 17:44:18 by jcongolo          #+#    #+#             */
/*   Updated: 2024/10/16 19:37:51 by jcongolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}
/* int main()
{
	char	nome[];
	printf("Introza o seu nome para te mostrar a longitude.\n");
	scanf("%s", nome);
	
	size_t length_mome;

	length_nome = ft_strlen(nome);
	printf("A longitude de : %s é : %zu caracteres. \n", nome, length_nome);
	
	return 0;
} */
