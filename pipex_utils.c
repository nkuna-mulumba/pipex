/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcongolo <jcongolo@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-03 15:16:43 by jcongolo          #+#    #+#             */
/*   Updated: 2025-03-03 15:16:43 by jcongolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
	Função que cria um pipe, esperando um array[2] de inteiros 
	para armazenar dois descritores de arquivo (fd).
	- fd[0]: Usado para leitura do pipe.
	- fd[1]: Usado para escrita no pipe.
	Se ocorrer um erro na criação do pipe, uma mensagem de erro é exibida
	e o programa termina com um código de saída de falha.
*/
void	create_pipe(int	*fd)
{
	if (pipe(fd) == -1)
	{
		perror("Error ao criar o pipe");
		exit(1);
	}
}
/*
	 Função para fechar os descritores de arquivo criados pelo pipe.
	- Fecha fd[0], que é usado para leitura.
	- Fecha fd[1], que é usado para escrita.
	Essa função garante que ambos os descritores de arquivo sejam fechados
	corretamente para evitar vazamentos de recursos.
*/
void	close_pipe(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}

/*
	Função que redireciona a entrada padrão (stdin) para um arquivo.
	- file: Nome do arquivo a ser usado como entrada.
	Se ocorrer um erro ao abrir o arquivo, uma mensagem de erro é exibida
	e o programa termina com um código de saída de falha.
*/
void	redir_input(const char *file)
{
	int	input_file;
	
	// Abre o arquivo de entrada no modo somente leitura
	input_file = open(file, O_RDONLY);
	if (input_file == -1)// Verifica se houve erro ao abrir o arquivo
	{
		perror("Erro ao abrir o arquivo de entrada");
		exit(1);
	}
	// Redireciona a entrada padrão (stdin) para o arquivo de entrada
	if (dup2(input_file, STDIN_FILENO) ==-1)// Verifica se houve erro ao redirecionar
	{
		perror("Erro ao redicionar a entrada padrao");
		close(input_file);// Fecha o arquivo de entrada em caso de erro
		exit(1);
	}
	// Fecha o descritor de arquivo do arquivo de entrada
	close(input_file);
}
