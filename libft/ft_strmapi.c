/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcongolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 21:47:50 by jcongolo          #+#    #+#             */
/*   Updated: 2024/10/19 22:55:08 by jcongolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*s_f;
	size_t	i;

	if (!s || !f)
		return (NULL);
	s_f = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!s_f)
	{
		return (NULL);
	}
	i = 0;
	while (i < ft_strlen(s))
	{
		s_f[i] = f(i, s[i]);
		i++;
	}
	s_f[i] = '\0';
	return (s_f);
}

char	func_apl(unsigned int i, char c)
{
	return (c + i);
}
/*
int main()
{
	char const *um = "aaaa";
	char	*um_func = ft_strmapi(um, func_apl);

	if (um_func)
	{
		printf("%s\n", um_func);
		free(um_func);
	}
	else
	{
		return (0);
	}
	return 0;
}
*/
