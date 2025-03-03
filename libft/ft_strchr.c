/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcongolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 18:44:23 by jcongolo          #+#    #+#             */
/*   Updated: 2024/10/17 16:27:50 by jcongolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	*str;

	str = (char *)s;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == (char)c)
		{
			return (&str[i]);
		}
		i++;
	}
	if (str[i] == (char)c)
	{
		return (&str[i]);
	}
	return (NULL);
}
/*
int main()
{
	const char	*str = "helo world";
	int	c = 'a';
	char	*ocorrencia = ft_strchr(str, c);
	if(ocorrencia)
	{
		printf("%s\n", ocorrencia);
	}
	else
	{
		printf("Caractere nao encontrado\n");
	}
	return 0;
}
*/
