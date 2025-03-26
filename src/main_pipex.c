/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcongolo <jcongolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:33:37 by jcongolo          #+#    #+#             */
/*   Updated: 2025/03/26 01:24:40 by jcongolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

/**/
int	main(int argc, char **argv, char **env)
{
	int pipe_fd[2];// Array para os descritores do pipe (leitura e escrita).
	pid_t id1;// Identificador do processo (PID) do primeiro comando.
	pid_t id2;// Identificador do processo (PID) do segundo comando.
	int status;// Variável para armazenar o estado dos processos filhos.
	if (argc != 5)
	{
		write(2, "Usage: ./pipex infile cmd1 cmd2 outfile\n", 41);
		return (1);z
	}
	// Cria um pipe para comunicação entre os processos.
	if (pipe(pipe_fd) == -1)
	{
		// Exibe mensagem de erro se o pipe não puder ser criado.
		perror("Pipex: pipe");
		return (1);
	}
	// Executa o primeiro comando no processo filho e salva o PID.
	id1 = ft_cmd1(argv, env, pipe_fd);
	if (id1 == -1) // Verifica erro na execução do 1º comando.
	{
		// Fecha os descritores do pipe e encerra o programa.
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		return (1);
	}
	// Executa o segundo comando no processo filho e salva o PID.
	id2 = ft_cmd2(argv, env, pipe_fd, argc);
	// Fechar descritores do pipe no processo pai.
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	// Aguarda o término do processo do primeiro comando.
	waitpid(id1, NULL, 0);
	// Aguarda o término do processo do segundo comando e captura seu status.
	waitpid(id2, &status, 0);
	// Verifica se o segundo processo filho terminou normalmente.
	if (WIFEXITED(status)) // Se o filho terminou normalmente
	{
		// Retorna o código de saída do segundo comando.
		return (WEXITSTATUS(status)); // Retorna seu código de saída
	}
	return (1);
}
