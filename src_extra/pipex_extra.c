/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_extra.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcongolo <jcongolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 17:02:35 by jcongolo          #+#    #+#             */
/*   Updated: 2025/03/23 15:58:39 by jcongolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

/**
 * ft_exec_intermediate_cmd - Executa um comando intermediário no pipeline.
 * Redireciona a entrada do pipe anterior e a saída para o próximo pipe.
 * Cria um processo filho para a execução do comando, gerenciando os pipes
   necessários.
 */
static void	ft_exec_intermediate_cmd(char *cmd, int *fd_in, int *pipe_fd,
		char **env)
{
	pid_t	pid;

	if (pipe(pipe_fd) == -1)
	{
		perror("Error: pipe");
		exit(1);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("Error: fork");
		exit(1);
	}
	if (pid == 0) // Processo filho
	{
		close(pipe_fd[0]);          // Fechar leitura do pipe
		dup2(*fd_in, STDIN_FILENO); // Redirecionar entrada para fd_in
		close(*fd_in);
		dup2(pipe_fd[1], STDOUT_FILENO); // Redirecionar saída para o pipe
		close(pipe_fd[1]);
		ft_exec_cmd_chek(cmd, env); // Executar comando
		exit(1);                    // Se o comando falhar
	}
	else // Processo pai
	{
		close(pipe_fd[1]);   // Fechar escrita no pipe
		close(*fd_in);       // Fechar descritor de entrada usado
		*fd_in = pipe_fd[0]; // Atualizar entrada para o próximo comando
	}
}

/*
 * ft_exec_last_cmd - Executa o último comando no pipeline.
 * Redireciona a entrada do último pipe e a saída para o arquivo de saída.
 * Gerencia a criação de um processo filho e manipula o arquivo de saída.
 */
static void	ft_exec_last_cmd(char *cmd, int fd_in, char *outfile, char **env, int in)
{
	int		fd_out;
	pid_t	pid;

	// Abrir arquivo de saída
	if (!in)
		fd_out = open(outfile, O_CREAT | O_WRONLY | O_TRUNC, 0744);
	else
		fd_out = open(outfile, O_CREAT | O_WRONLY | O_APPEND, 0744);
	if (fd_out < 0)
	{
		perror("Error: open outfile");
		exit(2);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("Error: fork");
		exit(1);
	}
	if (pid == 0) // Processo filho
	{
		dup2(fd_in, STDIN_FILENO);   // Redirecionar entrada do último pipe
		dup2(fd_out, STDOUT_FILENO); // Redirecionar saída para o arquivo
		close(fd_in);
		close(fd_out);
		ft_exec_cmd_chek(cmd, env); // Executar o último comando
		exit(1);                    // Se o comando falhar
	}
	else // Processo pai
	{
		close(fd_in);  // Fechar entrada do último pipe
		close(fd_out); // Fechar arquivo de saída
	}
}

/**
 * ft_exec_multiple_pipes - Controla o pipeline completo de comandos.
 * Gerencia os arquivos de entrada e saída e organiza a execução dos
 * comandos intermediários e o último comando no pipeline.
 */
void	ft_exec_multiple_pipes(int argc, char **argv, char **env, int in)
{
	int	fd_in;
	int	pipe_fd[2];
	int	i;

	// Abrir arquivo de entrada
	if (!in)
	{
		fd_in = open(argv[1], O_RDONLY);
		if (fd_in < 0)
		{
			perror("Error: open infile");
			exit(2);
		}
	}
	else
		fd_in = in;
	// Executar comandos intermediários
	i = 2 - (in != 0); // Começa no primeiro comando
	while (i < argc - 2)
	{
		ft_exec_intermediate_cmd(argv[i], &fd_in, pipe_fd, env);
		i++;
	}
	// Executar o último comando
	ft_exec_last_cmd(argv[argc - 2], fd_in, argv[argc - 1], env, in);
	// Esperar processos filhos
	i = -1;
	while (++i < argc - 2 - (in != 0))
		wait(NULL);
}

/*
** ft_here_doc:
** - Lê entrada interativa até o LIMITADOR ser digitado.
** - Escreve o conteúdo coletado em um pipe.
** - Redireciona STDIN para esse pipe e chama ft_exec_multiple_pipes para
**   executar os comandos, ignorando os dois primeiros argumentos
	("here_doc" e LIMITADOR).
*/
void	ft_here_doc(char *limiter, int argc, char **argv, char **env)
{
	int		fd[2];
	char	*line;
	char	*limiter_with_newline;

	limiter_with_newline = ft_strjoin(limiter, "\n");
	if (!limiter_with_newline)
	{
		perror("Error: malloc");
		exit(1);
	}
	if (pipe(fd) == -1) // Criar um pipe
		(perror("Error: pipe"), exit(1));
	while (1)
	{
		write(1, "> ", 3);
		// Ler entrada no usuario
		line = ft_get_next_line(STDIN_FILENO);
		// Verificar o limitador
		if (!line || ft_strcmp(line, limiter_with_newline) == 0)
		{
			break ;
		}
		write(fd[1], line, ft_strlen(line)); // Escrever no pipe
		// Liberar a memoria alocada na linha
		free(line);
	}
	if (line)
	{
		free(line); // Liberar a ultima linha lida
	}
	// Fechar escrita do pipe no processo do pai
	close(fd[1]);
	// Liberar o limitador com '\n'
	free(limiter_with_newline);
	// Executar comandos
	ft_exec_multiple_pipes(argc - 2, argv + 2, env, fd[0]);
}
