/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcongolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 12:12:05 by jcongolo          #+#    #+#             */
/*   Updated: 2024/10/10 21:16:26 by jcongolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	char	*s1_s2;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	s1_s2 = (char *)malloc(len_s1 + len_s2 + 1);
	if (!s1_s2)
		return (NULL);
	ft_strlcpy(s1_s2, s1, len_s1 + 1);
	ft_strlcat(s1_s2, s2, len_s1 + len_s2 + 1);
	return (s1_s2);
}
/*
int main()
{
	char const	*um = "Nkuna";
	char const *dois = "Mulumba";
	char	*um_dois = ft_strjoin(um, dois);
	if (um_dois)
	{
		printf("%s\n :", um_dois);
		free(um_dois);
	}
	else
	{
		return (0);
	}
	return 0;
}
*/
