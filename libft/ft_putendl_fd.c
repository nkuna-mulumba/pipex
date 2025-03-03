/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcongolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 19:38:00 by jcongolo          #+#    #+#             */
/*   Updated: 2024/10/09 17:33:13 by jcongolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	write(fd, "\n", 1);
}
/*
int main()
{
      int arq_fd = open("arquivo.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
 
      if(arq_fd == -1)
      {
          perror("Erro de abrir o arquivo");
          return 1;
      }
 
      ft_putendl_fd("Ola Nkuna", arq_fd);
      close(arq_fd);
      return 0;
 }
*/
