/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcongolo <jcongolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:16:43 by jcongolo          #+#    #+#             */
/*   Updated: 2025/03/26 00:12:58 by jcongolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

/*
	funçao que busca a variável de ambiente PATH
	-> env: Array de strings com as variáveis de ambiente
	-> return: Valor da variável PATH ou NULL se não encontrada
*/
char	*ft_get_path_variable(char **env)
{
	int	i;

	i = 0;
	// Iterar sobre as variaveis de ambiente
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
	Função para obter e dividir a variável PATH.
	-> param env: Array de strings com as variáveis de ambiente.
	-> return: Array de diretórios da variável PATH ou NULL se
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
		return (NULL);
	}
	// Dividir PATH em diretórios
	path_split = ft_split(path, ':');
	if (!path_split)
	{
		free(path);
		return (NULL);
	}
	return (path_split);
}

/*
	Função para localizar o caminho completo do executável.
	-> s_cmd: Array de strings com o comando e argumentos.
	-> path_split: Array de diretórios da variável PATH.
	-> return: Caminho completo do executável ou NULL se não
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
		exit(1);
	// Percorre os diretórios e tenta localizar o comando
	i = 0;
	while (path_split[i] != NULL)
	{
		// Concatena o diretório com o comando
		path = ft_strjoin(path_split[i], cmd);
		if (!path)
		{
			free(cmd);
			return (NULL);
		}
		// Verifica se o comando é executável
		if (access(path, F_OK | X_OK) == 0)
		{
			free(cmd);
			return (path); // Retorna o caminho completo encontrado
		}
		free(path);
		i++;
	}
	// Libera memória se comando não encontrado
	free(cmd);
	return (NULL);
}

/*
	Função para obter o caminho completo do executável.
	-> s_cmd: Array de strings com o comando e argumentos.
	-> env: Array de strings com as variáveis de ambiente.
	-> return: Caminho completo do executável ou NULL se não encontrado.
*/
char	*ft_locate_cmd(char **s_cmd, char **env)
{
	char	**path_split;
	char	*cmd_path;

	// Obtém e divide a variável PATH
	path_split = ft_get_and_split_path(env);
	if (!path_split)
	{
		ft_cmd_error(s_cmd[0]);
		return (NULL);
	}
	// Procura comando nos diretórios da PATH
	cmd_path = ft_concat_and_check_cmd(s_cmd, path_split);
	// Libera memória da divisão da PATH
	ft_free_array(path_split);
	return (cmd_path);
}

/*
	A funçao que libera memória de um array de strings
	-> array: Array de strings a ser liberado
*/
void	ft_free_array(char **array)
{
	size_t	i;

	if (!array)
		return ;
	i = 0;
	// Iterar e libarar cada string
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	// Liberar array
	free(array);
}
