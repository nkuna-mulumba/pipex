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
	1. Abre o arquivo no modo de leitura (O_RDONLY).
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
/*
	Função que redireciona a saída padrão (stdout) para um arquivo 
	especificado.
	- file: Nome do arquivo para o qual a saída padrão será redirecionada.
		1. Abre o arquivo no modo de escrita (O_WRONLY).
			- Cria o arquivo se ele não existir (O_CREAT).
			- Trunca o arquivo (zera o conteúdo) se ele já existir (O_TRUNC).
		2. Redireciona o descritor de saída padrão (STDOUT_FILENO) 
			para o descritor do arquivo aberto.
		3. Fecha o descritor do arquivo após o redirecionamento.
		- Exibe uma mensagem de erro caso o arquivo não possa ser aberto
		ou o redirecionamento falhe, encerrando o programa.
*/
void redir_output(const char *file)
{
	int	output_file;

	output_file = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (output_file == -1)
	{
		perror("Erro ao abrir o arquivo de saída");
		exit(1);
	}
	if (dup2(output_file, STDOUT_FILENO) == -1)
	{
		perror("Erro ao redirecionar a saída padrão");
		close(output_file);
		exit(1);
	}
	close(output_file);
}
