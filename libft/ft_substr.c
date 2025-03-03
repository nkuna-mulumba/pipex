/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcongolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 16:02:02 by jcongolo          #+#    #+#             */
/*   Updated: 2024/10/10 16:59:35 by jcongolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	char	*sub_s;
	size_t	i;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (len > s_len - start)
		len = s_len - start;
	sub_s = (char *)malloc(len + 1);
	if (!sub_s)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		sub_s[i] = s[start + i];
		i++;
	}
	sub_s[i] = '\0';
	return (sub_s);
}
/*
int main()
{
	const char	*string = "Hola mundo";
	char	*sub_string = ft_substr(string, 5, 4);
	if (sub_string)
	{
		printf("Substring tem como valor :%s:\n", sub_string);
	}
	else
	{
		return (0);
	}
	return 0;
}
*/
