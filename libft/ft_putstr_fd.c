/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcongolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 17:51:25 by jcongolo          #+#    #+#             */
/*   Updated: 2024/10/09 17:03:03 by jcongolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (fd >= 0)
	{
		while (s[i])
		{
			write(fd, &s[i], 1);
			i++;
		}
	}
}
/*
int main() 
{
	int arq_fd = open("test.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (arq_fd == -1) 
	{
		perror("Erro de abrir");
		return 1;
	}

	ft_putstr_fd("Olá, mundo!", fd);
	close(arq_fd); 
	return 0;
}
*/
