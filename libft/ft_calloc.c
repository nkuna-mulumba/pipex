/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcongolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 20:31:26 by jcongolo          #+#    #+#             */
/*   Updated: 2024/10/17 19:43:47 by jcongolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	total_size;
	void	*ptr;
	char	*ptr_ptr;
	size_t	i;

	total_size = nmemb * size;
	ptr = malloc(total_size);
	if (ptr == NULL)
	{
		return (NULL);
	}
	ptr_ptr = (char *)ptr;
	i = 0;
	while (i < total_size)
	{
		ptr_ptr[i] = 0;
		i++;
	}
	return (ptr);
}
/*
int main()
{
	size_t	num = 10;
	size_t	size = sizeof(int);

	int	*ini = (int *)ft_calloc(num, size);

	if (ini == NULL)
	{
		printf("Alocação da memória falhou.\n");
		return 0;
    }
	size_t i = 0;
	while (i < num)
	{
		printf("Valor inicializado é de: %d\n", ini[i]);
		i++;
    }
	printf("\n");
	return 0;
}
*/
