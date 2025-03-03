/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcongolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:01:24 by jcongolo          #+#    #+#             */
/*   Updated: 2024/10/17 20:40:36 by jcongolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*last;
	int		s_len;

	s_len = 0;
	while (s[s_len] != '\0')
	{
		s_len++;
	}
	last = NULL;
	while (s_len >= 0)
	{
		if (s[s_len] == (unsigned char)c)
		{
			last = (char *)&s[s_len];
			break ;
		}
		s_len--;
	}
	return (last);
}
/*
int main()
{
	const char	nome[]= "Nkuna";
	char	caract = 'u';
	char	*ocorrencia = ft_strrchr(nome, caract);

	if (ocorrencia != NULL)
	{
		printf("Ocorrencia %c é encontrada em %s\n", caract, nome);
	}
	else
	{
		printf("Ocorrenca %c nao encontrada em %s\n", *correncia, nome);
	}
	return 0;
}
*/
