/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcongolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 21:02:01 by jcongolo          #+#    #+#             */
/*   Updated: 2024/10/19 22:59:12 by jcongolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int		i;

	i = 0;
	while (s[i] != '\0')
	{
		f(i, &s[i]);
		i++;
	}
}

void	apli_func(unsigned int i, char *c)
{
	*c = *c + i;
}
/* 
int main()
{
	char *str = "abc";
	printf("%s\n", str);
	ft_striteri(str, apli_func);
	printf("%s\n", str);
	return 0;
}
*/
