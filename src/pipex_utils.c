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
	@param env: Array de strings com as variáveis de ambiente
	@return: Valor da variável PATH ou NULL se não encontrada
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
	A funçao que libera memória de um array de strings
	@param tab: Array de strings a ser liberado
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

/*
	A funça para exibir mensagem de erro e
	encerra o programa em caso de nao encontrar cmd
	@param cmd: Comando que causou o erro
	@return: Não retorna (encerra o programa)
*/
int	ft_cmd_error(char *cmd)
{
	write(2, "Pipex invalid command: ", 24); // Mensagem de erro no stderr(2)
	write(2, cmd, ft_strlen(cmd));
	write(2, "\n", 1);
	return (0);
}

/*
	Funçao para exibir mensagem de erro sobre o arquivo e encerra o programa.
	@param filename: Nome do arquivo relacionado ao erro.
	@return: Não retorna (termina com exit(1)).
*/
void	ft_file_error(char *filename)
{
	perror(filename); // Exibe mensagem padrão de erro baseada no sistema.
	exit(1);// Encerra o programa com código de erro.
}

/*
	Verifica se a string do comando está vazia ou contém apenas
	espaços em branco.
	Chama ft_cmd_error se estiver vazia.
	@param cmd: String do comando a ser verificada

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
*/


/*
	Funçao para fecha os descritores de arquivo do pipe
	e exibe uma mensagem de erro
	@param fd: Array com os descritores de arquivo do pipe
	@param file: Nome do arquivo associado ao erro

void	ft_pipe_error(int *fd, char *file)
{
	close(fd[0]);
	close(fd[1]);
	perror(file);
}
*/