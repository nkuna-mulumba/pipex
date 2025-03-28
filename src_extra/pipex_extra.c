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

/*
 * Funçao que executa um comando intermediário no pipeline.
 *->pipex: Estrutura contendo dados do pipeline (cmd atual, argmentos e env)
 *->fd_in: Ponteiro do descritor de entrada (recebe entrada do pipe anterior)
 *->pipe_fd: Ponteiro do pipe atual (para redirecionar saída deste comando)
 *Descrição:
 * - Redireciona a entrada do pipe anterior para o comando atual.
 * - Cria um processo filho para executar o comando, gerenciando pipes.
 * - Atualiza fd_in para o próximo comando no pipeline.
 */
static void	ft_exec_intermediate_cmd(t_pipex *pipex, int *fd_in, int *pipe_fd)
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
		close(pipe_fd[0]);// Fechar leitura do pipe
		dup2(*fd_in, STDIN_FILENO); // Redirecionar entrada para fd_in
		close(*fd_in);
		dup2(pipe_fd[1], STDOUT_FILENO); // Redirecionar saída para o pipe
		close(pipe_fd[1]);
		ft_exec_cmd_chek(pipex->cmd, pipex->env); // Executar comando
		exit(1);// Se o comando falhar
	}
	else // Processo pai
	{
		close(pipe_fd[1]);   // Fechar escrita no pipe
		close(*fd_in);// Fechar descritor de entrada usado
		*fd_in = pipe_fd[0]; // Atualizar entrada para o próximo comando
	}
}

/*
 * Funçao para executar o último comando no pipeline.
 *->pipex: Estrutura contendo dados do pipeline (comando atual, argumentos e env).
 *->fd_in: Descritor de entrada (recebe a entrada do último pipe).
 *->outfile: Nome do arquivo de saída onde o resultado final será armazenado.
 *->in: Flag indicando o modo:
 *		- 0: Modo normal (sobrescrever arquivo de saída).
 *		- 1: Modo here_doc (adicionar ao final do arquivo de saída).
 * Descrição:
 * - Redireciona entrada do último pipe para o comando final.
 * - Redireciona saída para o arquivo especificado (modo truncar ou append).
 * - Cria um processo filho para executar o comando.
 */
static void	ft_exec_last_cmd(t_pipex *pipex, int fd_in, char *outfile, int in)
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
		dup2(fd_in, STDIN_FILENO);// Redirecionar entrada do último pipe
		dup2(fd_out, STDOUT_FILENO); // Redirecionar saída para o arquivo
		close(fd_in);
		close(fd_out);
		ft_exec_cmd_chek(pipex->cmd, pipex->env); // Executar o último comando
		exit(1);// Se o comando falhar
	}
	else // Processo pai
	{
		close(fd_in);  // Fechar entrada do último pipe
		close(fd_out); // Fechar arquivo de saída
	}
}

/*
 * Funçao para controlar o pipeline completo de comandos
 *->argc: Número de argumentos (para determinar número de cmd)
 *->pipex: Estrutura com dados do pipeline (cmd atual, argmentos e env)
 *->in: Descritor de entrada:
 *		- 0: Indica entrada inicial modo normal (arquivo)
 *		- 2: Indica entrada inicial modo here_doc (pipe)
 * Descrição:
 * - Abre o arquivo de entrada ou utiliza o pipe criado no modo here_doc
 * - Executa comandos intermediários redirecionando entrada e saída
 * - Finaliza com o último cmd, armazenando saída no arquivo especificado
 */
void	ft_exec_multiple_pipes(int argc, t_pipex *pipex, int in)
{
	int	fd_in;
	int	pipe_fd[2];
	int	i;

	// Abrir arquivo de entrada
	if (!in)
	{
		fd_in = open(pipex->argv[1], O_RDONLY);
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
		pipex->cmd = pipex->argv[i];
		ft_exec_intermediate_cmd(pipex, &fd_in, pipe_fd);
		i++;
	}
	// Executar o último comando
	pipex->cmd = pipex->argv[argc - 2];
	ft_exec_last_cmd(pipex, fd_in, pipex->argv[argc - 1], in);
	// Esperar processos filhos
	i = -1;
	while (++i < argc - 2 - (in != 0))
		wait(NULL);
}

/**
 * Funçao que gerencia o modo here_doc.
 * ->limiter: String que define o limitador(termina a leitura interativa)
 * ->pip: Estrutura com dados do pipeline (ajustada para ignorar here_doc e LIMITER)
 * Descrição:
 * - Lê entradas interativas do usuário até que LIMITER seja encontrado
 * - Escreve as entradas no pipe criado e redireciona para pipeline.
 * - Ajusta argumentos de `pip` para ignorar os dois primeiros (here_doc e LIMITER)
 */
void	ft_here_doc(char *limiter, t_pipex *pip)
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
	pip->argv += 2;
	ft_exec_multiple_pipes(pip->argc - 2, pip, fd[0]);
}
