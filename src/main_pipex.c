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

/*
	Funçao para executa o 1º comando.
	Redireciona entrada do arquivo e saída para o pipe.
	-> argv: Argumentos passados ao programa.
	-> env: Variáveis de ambiente.
	-> file_pipe: Descritores do pipe.
	-> return: PID do processo filho ou -1 em caso de erro.
*/
pid_t	ft_cmd1(char **argv, char **env, int *file_pipe)
{
	pid_t	pid;
	int		fd;

	// Abre o arquivo de entrada para leitura
	fd = ft_open_file(argv[1], O_RDONLY, 0);
	if (fd < 0)
	{
		return (-1);
	}
	// Cria o processo filho
	pid = fork();
	if (pid == -1)
	{
		close(fd);
		perror("Pipex: fork");
		exit(1);
	}
	// No processo filho
	if (pid == 0)
	{
		// Configura entrada e saída
		ft_redirect_io(fd, file_pipe[1]);
		close(fd);// Fecha arquivo
		close(file_pipe[0]);// Fecha leitura do pipe
		close(file_pipe[1]);// Fecha escrita do pipe
		ft_exec_cmd_chek(argv[2], env); // Executa o comando
	}
	// No processo pai, fecha arquivo de entrada
	close(fd);
	// Retorna PID do filho
	return (pid);
}

/*
	Funçao para executar o 2º comando.
	Redireciona entrada do pipe e saída para o arquivo de saída.
	-> argv: Argumentos passados ao programa.
	-> env: Variáveis de ambiente.
	-> file_pipe: Descritores do pipe.
	-> argc: Número de argumentos.
	-> return: PID do processo filho.
*/
pid_t	ft_cmd2(char **argv, char **env, int *file_pipe, int argc)
{
	pid_t	pid;
	int		fd;

	pid = fork();
	if (pid == -1)
	{
		perror("Pipex: fork");
		exit(1);
	}
	if (pid == 0)
	{
		// Abre o arquivo de saída
		fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
		{
			ft_file_error(argv[argc - 1]); // Erro ao abrir arquivo de saída
		}
		// Redireciona entrada do pipe e saída para o arquivo
		ft_redirect_io(file_pipe[0], fd);
		// Fecha descritores no processo filho
		close(fd);
		close(file_pipe[0]);
		close(file_pipe[1]);
		// Executa o comando
		ft_exec_cmd_chek(argv[argc - 2], env);
	}
	return (pid);
}

/*
int	main(int argc, char **argv, char **env)
{
	int pipe_fd[2];// Descritores do pipe
	pid_t id[2];// IDs dos processos filhos
	int process_status; // Status dos filhos
	if (argc != 5)
	{
		write(2, "Usage: ./pipex infile cmd1 cmd2 outfile\n", 41);
		exit(1);
	}
	if (pipe(pipe_fd) == -1)
	{
		perror("Error:");
		exit(1);
	}
	id[0] = ft_cmd1(argv, env, pipe_fd);// Executa cmd1
	id[1] = ft_cmd2(argv, env, pipe_fd, argc);// Executa cmd2
	close(pipe_fd[0]); // Fecha leitura do pipe
	close(pipe_fd[1]); // Fecha escrita do pipe
	waitpid(id[0], &process_status, 0); // Espera cmd1 terminar
	waitpid(id[1], &process_status, 0); // Espera cmd2 terminar
	exit(WEXITSTATUS(process_status)); // Sai com o status de cmd2
	return (0);
}
*/

