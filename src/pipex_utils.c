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

#include "../include/pipex.h"

/*
	Funçao para fecha os descritores de arquivo do pipe 
	e exibe uma mensagem de erro
	@param fd: Array com os descritores de arquivo do pipe
	@param file: Nome do arquivo associado ao erro
*/
void	ft_pipe_error(int *fd, char *file)
{
	close(fd[0]);
	close(fd[1]);
	perror(file);
}
/*
	funçao que busca a variável de ambiente PATH
	@param env: Array de strings com as variáveis de ambiente
	@return: Valor da variável PATH ou NULL se não encontrada

*/
char	*ft_get_path_variable(char **env)
{
	int	i;

	i = 0;
	//Iterar sobre as variaveis de ambiente
	while (env[i])
	{
		// Verifica se a variável começa com "PATH="
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			// Retorna o valor da variável PATH
			return (env[i] + 5);
		}
		i++;
	}
	// Retorna NULL se PATH não for encontrada
	return (NULL);
}

/*
	A funçao que libera memória de um array de strings
	@param tab: Array de strings a ser liberado
*/
void	ft_free_array(char **array)
{
	size_t	i;
	if (!array)
		return ;
	i = 0;
	//Iterar e libarar cada string
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	//Liberar array
	free(array);
}

/*
	A funça para exibir mensagem de erro e 
	encerra o programa em caso de nao encontrar cmd
	@param cmd: Comando que causou o erro
	@return: Não retorna (encerra o programa)
*/
int	ft_cmd_error(char *cmd)
{
	write(2, "Invalid command: ", 17);// Mensagem de erro no stderr(2)
	write(2, cmd, ft_strlen(cmd));
	write(2, "\n", 1);
	return (0);
}

/*
	Verifica se a string do comando está vazia ou contém apenas 
	espaços em branco.
	Chama ft_cmd_error se estiver vazia.
	@param cmd: String do comando a ser verificada
*/
void	ft_empty(char *cmd)
{
	while ((*cmd >= 9 && *cmd <= 13) || *cmd == ' ')
	{
		cmd++;
	}
	if (*cmd == '\0')
	{
		ft_cmd_error(cmd);
	}
}

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
	Executa um comando com seus argumentos
	@param full_cmd: Array de strings com o comando e seus argumentos
	@param env: Array de strings com as variáveis de ambiente
	@return: Código de saída do comando
void	ft_exec_command(char **cmd_s, char **env)
{
	char	*path;

	// Verificar se o comando está vazio
	ft_empty(cmd_s[0]);
	if (*cmd_s[0] == '\0')
		return ;

	// Obtém o caminho completo do comando
	path = ft_get_path(cmd_s, env);
	if (path == NULL)
	{
		ft_cmd_error(cmd_s[0]);
		return ;
	}
	// Executa o comando
	if (execve(path, cmd_s, env) == -1)
	{
		free(path);
		ft_cmd_error(cmd_s[0]);
		return ;
	}
	free(path);
}

*/

