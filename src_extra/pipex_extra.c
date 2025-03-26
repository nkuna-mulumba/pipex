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
 * Redireciona a entrada do pipe anterior para o comando atual e conecta a
 * saída do comando atual ao próximo pipe. Gerencia o processo filho para
 * executar o comando.
 */
static void	ft_exec_mid_cmd(char *cmd, int *fd_in, int *pipe_fd, char **env)
{
	//Criar proccesso
	pid_t	pid;

	// Erro ao criar o pipe
	if (pipe(pipe_fd) == -1)
	{
		perror("Error: pipe");
		exit(1);
	}
	// Erro ao criar o processo filho
	pid = fork();
	if (pid == -1)
	{
		perror("Error: fork");
		exit(1);
	}
	// Processo filho
	if (pid == 0)
	{
		close(pipe_fd[0]);// Fechar leitura do pipe
		ft_redirect_io(*fd_in, pipe_fd[1]); // Redirecionar entrada e saída
		close(*fd_in);
		close(pipe_fd[1]);
		ft_exec_cmd_chek(cmd, env);// Executar comando
		exit(1);// Se o comando falhar
	}
	else // Processo pai
	{
		close(pipe_fd[1]);// Fechar escrita no pipe
		close(*fd_in);// Fechar descritor de entrada usado
		*fd_in = pipe_fd[0];// Atualizar entrada para o próximo comando
	}
}


/*
 * ft_exec_last_cmd - Executa o último comando no pipeline.
 * Redireciona a entrada do último pipe e a saída para o arquivo de saída.
 * Gerencia a criação de um processo filho e manipula o arquivo de saída.

static void	ft_exec_last_cmd(char *cmd, int fd_in, char *outfile, char **env, int in)
{
	int		fd_out;// Arquivo de saída
	pid_t	pid;// Processo filho

	// Abrir arquivo de saída no modo apropriado (apêndice ou truncamento)
	fd_out = ft_open_file(outfile, O_WRONLY | O_CREAT | (in ? O_APPEND : O_TRUNC), 1);
	// Criar processo filho
	pid = fork();
	// Erro no fork
	if (pid == -1)
	{
		perror("Error: fork");
		exit(1);
	}
	//Processo filho
	if (pid == 0)
	{
		ft_redirect_io(fd_in, fd_out); // Redirecionar entrada e saída
		close(fd_in);
		close(fd_out);
		ft_exec_cmd_chek(cmd, env);// Executar último comando
		exit(1);// Se o comando falhar
	}
	else // Processo pai
	{
		close(fd_in);  // Fechar entrada do último pipe
		close(fd_out); // Fechar arquivo de saída
	}
}
 */

/*
 * ft_setup_and_exec - Configura e executa o comando no processo filho.
 * @fd_in:   Descritor de entrada (pipe ou arquivo)
 * @fd_out:  Descritor de saída (arquivo)
 * @cmd:     Comando a ser executado
 * @env:     Variáveis de ambiente
 */
static void ft_setup_and_exec(int fd_in, int fd_out, char *cmd, char **env)
{
	pid_t pid;

	pid = fork();
	if (pid == -1) {
		perror("pipex: fork");
		exit(EXIT_FAILURE);
	}
	// Processo filho
	if (pid == 0)
	{
		ft_redirect_io(fd_in, fd_out);
		close(fd_in);
		close(fd_out);
		ft_exec_cmd_chek(cmd, env);
		exit(EXIT_FAILURE); // Se ft_exec_cmd_chek falhar
    }
	else // Processo pai
	{
		close(fd_in);
		close(fd_out);
    }
}

/*
 * ft_exec_last_cmd - Executa o último comando no pipeline.
 * @cmd:-> Comando a ser executado
 * @fd_in:-> Descritor de entrada (pipe anterior)
 * @outfile:-> Arquivo de saída
 * @env:-> Variáveis de ambiente
 */
static void ft_exec_last_cmd(char *cmd, int fd_in, char *outfile, char **env) 
{
	int	flags;
	int	fd_out;
	
	flags = O_WRONLY | O_CREAT;
	if (ft_strcmp(cmd, "here_doc") == 0)
	{
		flags |= O_APPEND;  // Modo append para here_doc
	}
	else
	{
		flags |= O_TRUNC;   // Modo truncar para outros comandos
	}
	fd_out = ft_open_file(outfile, flags, 1);
	ft_setup_and_exec(fd_in, fd_out, cmd, env);
}




/*
 * ft_exec_multiple_pipes - Controla o pipeline completo de comandos.
 * Gerencia os arquivos de entrada e saída e organiza a execução dos
 * comandos intermediários e o último comando no pipeline.
 */
void	ft_exec_multiple_pipes(int argc, char **argv, char **env, int in)
{
	int	fd_in;
	int	pipe_fd[2];
	int	i;

	// Abrir arquivo de entrada em modo de leitura usando ft_open_file
	if (!in)
		fd_in = ft_open_file(argv[1], O_RDONLY, 0);
	else
		fd_in = in;

	// Loop para executar todos os comandos intermediários do pipeline
	i = 2 - (in != 0); // Começa no primeiro comando
	while (i < argc - 2)
	{
		ft_exec_mid_cmd(argv[i], &fd_in, pipe_fd, env);
		i++;
	}
	// Executar último cmd do pipeline e redirecionar saída para arquivo de destino
	// ft_exec_last_cmd(argv[argc - 2], fd_in, argv[argc - 1], env, in);
	ft_exec_last_cmd(argv[argc - 2], fd_in, argv[argc - 1], env);

	// Aguardar a conclusão de todos os processos filhos do pipeline
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
