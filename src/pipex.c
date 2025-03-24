 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuna <nkuna@student.42.fr>                #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-09 12:37:44 by nkuna             #+#    #+#             */
/*   Updated: 2025-03-09 12:37:44 by nkuna            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

/*
	Função para obter e dividir a variável PATH.
	@param env: Array de strings com as variáveis de ambiente.
	@return: Array de diretórios da variável PATH ou NULL se 
	não encontrada.
*/
static char	**ft_get_and_split_path(char **env)
{
	char	*path;
	char	**path_split;

	// Obter a variável PATH
	path = ft_get_path_variable(env);
	if (!path)
	{
		return(NULL);
	}

	// Dividir PATH em diretórios
	path_split = ft_split(path, ':');
	if (!path_split)
	{
		free(path);
		return(NULL);
	}
	return(path_split);
}

/*
	Função para localizar o caminho completo do executável.
	@param s_cmd: Array de strings com o comando e argumentos.
	@param path_split: Array de diretórios da variável PATH.
	@return: Caminho completo do executável ou NULL se não 
	encontrado.
*/
static char	*ft_concat_and_check_cmd(char **s_cmd, char **path_split)
{
	int		i;
	char	*path;
	char	*cmd;

	// Adiciona "/" em nome do comando
	cmd = ft_strjoin("/", s_cmd[0]);
	if (!cmd)
	{
		exit(1);
	}
	// Percorre os diretórios e tenta localizar o comando
	i = 0;
	while (path_split[i] != NULL)
	{
		// Concatena o diretório com o comando
		path = ft_strjoin(path_split[i], cmd);
		if (!path)
		{
			free(cmd);
			return(NULL);
		}
		// Verifica se o comando é executável
		if (access(path, F_OK | X_OK) == 0)
		{
			free(cmd);
			return(path);// Retorna o caminho completo encontrado
		}
		free(path);
		i++;
	}
	// Libera memória se comando não encontrado
	free(cmd);
	return(NULL);
}

/*
	Função para obter o caminho completo do executável.
	@param s_cmd: Array de strings com o comando e argumentos.
	@param env: Array de strings com as variáveis de ambiente.
	@return: Caminho completo do executável ou NULL se não encontrado.
*/
char	*ft_locate_cmd(char **s_cmd, char **env)
{
	char	**path_split;
	char	*cmd_path;

	//Obtém e divide a variável PATH
	path_split = ft_get_and_split_path(env);
	if (!path_split)
	{
		ft_cmd_error(s_cmd[0]);
		return(NULL);
	}
	//Procura comando nos diretórios da PATH
	cmd_path = ft_concat_and_check_cmd(s_cmd, path_split);

	// Libera memória da divisão da PATH
	ft_free_array(path_split);
	
	return(cmd_path);
}

/*
	A funçao que verifica e localiza o comando para execução.
	@param s_cmd: Array de strings resultante da divisão do comando.
	@param env: Array com as variáveis de ambiente do sistema.

	@return: Caminho completo do comando (absoluto, relativo ou 
	 encontrado no PATH).
	Se o comando for inválido ou não encontrado, a função termina com `exit`.
*/
static char	*ft_check_and_locate_cmd(char **s_cmd, char **env)
{
	char	*path;
	 //Verifica se o comando é absoluto (inicia com '/')
	if ((access(s_cmd[0], F_OK | X_OK) == 0) && (s_cmd[0][0] == '/'))
	{
		return(ft_strdup(s_cmd[0]));
	}
	//Verifica se o comando é relativo (inicia com './')
	if ((access(s_cmd[0], F_OK | X_OK) == 0) && (ft_strncmp(s_cmd[0], "./", 2) == 0))
	{
		return(ft_strdup(s_cmd[0]));
	}
	//Se o comando contém '/' mas não é acessível
	if (access(s_cmd[0], F_OK | X_OK) != 0 && ft_strchr(s_cmd[0], '/'))
	{
		ft_cmd_error(s_cmd[0]);
		ft_free_array(s_cmd);
		exit(127);
	}
	//Localiza comando nos diretórios da variável PATH
	path = ft_locate_cmd(s_cmd, env);
	if (!path)
	{
		ft_cmd_error(s_cmd[0]);
		ft_free_array(s_cmd);
		exit(127);
	}
	return(path);
}

/*
	Funçao que verifica, localiza e executa um comando fornecido.
	@param cmd: O comando a ser executado.
	@param env: Array com as variáveis de ambiente do sistema.

	A função divide o comando, verifica se é válido, localiza-o 
	(caso necessário) e tenta executá-lo. 
	Finaliza o processo em caso de erro ou sucesso.
*/
void	ft_exec_cmd_chek(char *cmd, char **env)
{
	char	**s_cmd;
	char	*path;

	//Verifica se o comando está vazio
	ft_empty(cmd);

	// Divide o comando em argumentos
	s_cmd = ft_split(cmd, ' ');
	if (!s_cmd || !s_cmd[0])
	{
		ft_free_array(s_cmd);
		exit(1);
	}
	// Verifica e localiza o comando
	path = ft_check_and_locate_cmd(s_cmd, env);

	// Executa o comando
	if (execve(path, s_cmd, env) == -1)
	{
		ft_cmd_error(s_cmd[0]);
		ft_free_array(s_cmd);
		free(path);
		exit(127);
	}
	// Libera memória
	ft_free_array(s_cmd);
	free(path);
	exit(0);
}

/*
	Funçao para executar o 1º comando, redirecionando a entrada 
	do arquivo e a saída para o pipe
	@param argv: Array de argumentos passados ao programa
	@param envp: Array de strings com as variáveis de ambiente
	@param file_pipe: Array com os descritores de arquivo do pipe
	@return: ID do processo filho
*/
pid_t	ft_cmd1(char **argv, char **env, int *file_pipe)
{
	pid_t	id; //Identificador do processo (PID)
	int		fd; //Descritor de arquivo para o arquivo de entrada
	
	id = fork();//Processo filho é criada
	if (id == -1)
		(perror("Error"), exit(1));
	if (id == 0)//Executar quando é processo filho
	{
		fd = open(argv[1], O_RDONLY);
		if (fd < 0)
		{
			ft_pipe_error(file_pipe, argv[1]);
			close(file_pipe[0]);// Fecha descritor de leitura do pipe
			close(file_pipe[1]);// Fecha descritor de escrita do pipe
			exit(1);
		}
		dup2(fd, STDIN_FILENO);//Redicionar para o arquivo de entrada
		dup2(file_pipe[1], STDOUT_FILENO);//Redicionar saida para descritor de escrita pipe
		close(file_pipe[0]);//Fechar Descritor de leitura pipe no processo filho
		close(file_pipe[1]);//Fechar Descritor de escrita do pipe no processo filho
		close(fd);//Fechar o descritor de arquivo de entrada
		ft_exec_cmd_chek(argv[2], env);//Verificar e executar comando fornecido
	}
	return (id);
}


/*
	Funçao para executar 2º comando, redirecionando a 
	entrada do pipe e a saída para o arquivo
	@param argv: Array de argumentos passados ao programa
	@param envp: Array de strings com as variáveis de ambiente
	@param file_pipe: Array com os descritores de arquivo do pipe
	@param argc: Número de argumentos passados ao programa
	@return: ID do processo filho
*/
pid_t	ft_cmd2(char **argv, char **env, int *file_pipe, int argc)
{
	pid_t	id;
	int		fd;

	id = fork();
	if (id == -1)
		(perror("Error"), exit(1));
	if (id == 0)
	{
		fd = open(argv [argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0744 );
		if (fd < 0)
		{
			ft_pipe_error(file_pipe, argv[argc - 1]);
			close(file_pipe[0]);// Fecha descritor de leitura do pipe
			close(file_pipe[1]);// Fecha descritor de escrita do pipe
			exit(1);
		}
		dup2(file_pipe[0], STDIN_FILENO);// Redirecionar entrada para descritor de leitura do pipe
		dup2(fd, STDOUT_FILENO);// Redirecionar saída para o arquivo de saída
		close(file_pipe[0]);// Fechar descritor de leitura do pipe no processo filho
		close(file_pipe[1]);// Fechar descritor de escrita do pipe no processo filho
		close(fd);// Fechar o descritor de arquivo de saída
		ft_exec_cmd_chek(argv[argc - 2], env);// Verificar e executar comando fornecido
	}
	return (id);
}
