/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcongolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 17:30:25 by jcongolo          #+#    #+#             */
/*   Updated: 2024/10/06 19:12:57 by jcongolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <fcntl.h>

void	ft_putchar_fd(char c, int fd)
{
	if (fd >= 0)
	{
		write (fd, &c, 1);
	}
}
/*
int main() {
	int fd = open("test.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd < 0)
	{
       perror("Error opening file");
       return 1;
	}

   char c;
   printf("Introduce un carácter: ");
   c = getchar(); 
   ft_putchar_fd(c, fd);

   close(fd);
   return 0;
}
*/
