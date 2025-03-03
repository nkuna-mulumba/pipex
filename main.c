/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcongolo <jcongolo@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-03 15:33:37 by jcongolo          #+#    #+#             */
/*   Updated: 2025-03-03 15:33:37 by jcongolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
// Testa a criação do pipe e encerramentos dos fd
int	main(void)
{
	int	fd[2];

	//Criar "pipe" com 2 fd entrada e saida
	int	test;
	create_pipe(fd);
	// Verifique se os descritores de arquivo foram criados
	if (fd[0] != -1 && fd[1] != -1)
	{
		printf("Pipe criado com sucesso\n");
	}
	else
	{
		printf("Falha ao criar o pipe\n");
	}
	//Encerrar fd criada por defeito com "pipe"
	close_pipe(fd);

	return (0);
}
*/

//Testar a redir_input()
int main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Usa %s <arquivo de entrada>\n", argv[0]);
		return (1);
	}
	
	redir_input(argv[1]);

	char	buffer[100];
	ssize_t bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);
	if (bytes_read == -1)
	{
		perror("Erro ao ler do stdin");
		return (1);
	}
	buffer[bytes_read] = '\0';
	printf("Conteudo do arquivo: %s\n",  buffer);
	return (0);
}