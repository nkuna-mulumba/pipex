/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcongolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 21:18:24 by jcongolo          #+#    #+#             */
/*   Updated: 2024/10/17 19:59:08 by jcongolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	len_s;
	char	*new_s;
	size_t	i;

	len_s = ft_strlen(s);
	new_s = (char *)malloc(len_s + 1);
	if (!new_s)
		return (NULL);
	i = 0;
	while (i < len_s)
	{
		new_s[i] = s[i];
		i++;
	}
	new_s[i] = '\0';
	return (new_s);
}
/*
int main()
{
	const char	um[]= "Nkuna wa Mulumba";
	char	*nova_str = ft_strdup(um);
	if (nova_str == NULL)
	{
		return (1);
	}
	else
	{
		printf("%s\n", nova_str);
	}
	return 0;
}
*/
