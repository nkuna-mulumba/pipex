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
	Funçao para obter o caminho completo do executável
	@param s_cmd: Array de strings com o comando e argumentos
	@param env: Array de strings com as variáveis de ambiente
	@return: Caminho completo do executável ou NULL se não encontrado
*/
char	*ft_locate_cmd(char **s_cmd, char **env)
{
	int		i;
	char	*path;
	char	*error;
	char	*cmd;
	char	**path_split;

	//Encotrar variavel PATH
	path = ft_get_path_variable(env);
	if (path == NULL)
	{
		// Se PATH não é encontrada, retorna um erro
		error = ft_strdup(s_cmd[0]);
		ft_cmd_error(error);
		free(error);
	}
	// Concatena "/" ao nome do comando
	cmd = ft_strjoin("/", s_cmd[0]);
	if (!cmd)
		exit(1);
	// Dividir variavel PATH em diretórios
	path_split = ft_split(path, ':');
	if (!path_split)
		return(free(cmd), NULL);
	i = 0;
	while (path_split[i] != NULL)
	{
		// Concatena o diretório com o comando
		path = ft_strjoin(path_split[i], cmd);
		// Verifica se o comando existe e é executável
		if (access(path, F_OK | X_OK) == 0)
		{
			free(cmd);
			ft_free_array(path_split);
			return (path);
		}
		free(path);
		i++;
	}
	// Libera a memória e retorna NULL se o comando não for encontrado
	ft_free_array(path_split);
	free(cmd);
	return (NULL);
}

/*
	Funçao para verificar e executar um comando
	@param cmd: Comando a ser verificado e executado
	@param env: Array de strings com as variáveis de ambiente
*/
void	ft_exec_cmd_chek(char *cmd, char **env)
{
	char	*path;
	char	**s_cmd;

	ft_empty(cmd);
	// Dividir o comando em argumentos separado espaço
	s_cmd = ft_split(cmd, ' ');
	if (!s_cmd || !s_cmd[0])
		(ft_free_array(s_cmd), exit(1));
	//Verifica caminho do comando é absoluto "/"
	if ((access(s_cmd[0], F_OK | X_OK) == 0) && (s_cmd[0][0] == '/'))
	{
		//Se caminho é absoluto, executa
		if (execve(s_cmd[0], s_cmd, env) == -1)//Caso falhar
		{
			ft_cmd_error(s_cmd[0]);
			ft_free_array(s_cmd);
			exit(127);
		}
	}
	//Verifica caminho do comando é RELATIVO "./"
	if ((access(s_cmd[0], F_OK | X_OK) == 0) && (ft_strncmp(s_cmd[0], "./", 2)))
	{
		//Se caminho é relativo, executa
		if (execve(s_cmd[0], s_cmd, env) == -1)//Caso falhar
		{
			ft_cmd_error(s_cmd[0]);
			ft_free_array(s_cmd);
			exit(127);
		}
	}
	// Se o comando não é acessible e contem "/"
	else if ((access(s_cmd[0], F_OK | X_OK) != 0) && (ft_strchr(s_cmd[0], '/')))
	{
		ft_cmd_error(s_cmd[0]);
		ft_free_array(s_cmd);
		exit(127);
	}
	else
	{
		// Obtém o caminho completo do comando
		path = ft_locate_cmd(s_cmd, env);
		// Executa o comando se encontrado
		if (path ==  NULL || execve(path, s_cmd, env) == -1)
		{
			ft_cmd_error(s_cmd[0]);
			ft_free_array(s_cmd);
			exit(127);
		}
		ft_free_array(s_cmd);
		free(path);
		exit(0);
	}
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
