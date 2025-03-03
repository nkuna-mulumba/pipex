/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcongolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 15:22:52 by jcongolo          #+#    #+#             */
/*   Updated: 2024/10/17 21:03:00 by jcongolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*sub_s1;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	end = ft_strlen(s1);
	while (end > start && ft_strchr(set, s1[end - 1]))
		end--;
	sub_s1 = ft_substr(s1, start, end - start);
	return (sub_s1);
}

/*
int main()
{
	char const	*um = "zHola Mundoz";
	char const	*dois = "z";
	char	*sub_um = ft_strtrim(um, dois);
	if(sub_um)
	{
		printf("%s\n", sub_um);
		free(sub_um);
	}
	else
	{
		return (0);
	}
	return 0;
}
*/
