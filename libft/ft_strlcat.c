/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcongolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 13:19:50 by jcongolo          #+#    #+#             */
/*   Updated: 2024/10/16 21:55:37 by jcongolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	src_len;
	size_t	dst_len;

	src_len = 0;
	dst_len = 0;
	while ((dst[dst_len] != '\0') && (dst_len < size))
		dst_len++;
	while (src[src_len] != '\0')
		src_len++;
	if (dst_len == size)
		return (size + src_len);
	i = 0;
	while ((src[i] != '\0') && ((dst_len + i) < (size - 1)))
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	if ((dst_len + i) < size)
		dst[dst_len + i] = '\0';
	return (dst_len + src_len);
}
/*
int main()
{
	char	dst[20] = "Helo, ";
	const char	src[] = "World";

	size_t result = ft_strlcat(dst, src, sizeof(dst));
	
	printf("%s\n", dst);
	
	return 0;
}
*/
