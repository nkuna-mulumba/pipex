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

#include "pipex.h"

/*
	funçao que busca a variável de ambiente PATH
	@param envp: Array de strings com as variáveis de ambiente
	@return: Valor da variável PATH ou NULL se não encontrada

*/
char	*ft_find_path(char **envp)
{
	char	*value_path;

	//Iterar sobre as variaveis de ambiente
	while (*envp != NULL)
	{
		value_path = *envp++;
		// Verifica se a variável começa com "PATH="
		if (ft_strncmp(value_path, "PATH=", 5) == 0)
		{
			// Retorna o valor da variável PATH
			value_path = value_path + 5;
			return (value_path);
		}
	}
	// Retorna NULL se PATH não for encontrada
	return (NULL);
}

/*
	A funçao que libera memória de um array de strings
	@param tab: Array de strings a ser liberado
*/
void	ft_free_memory(char **tab)
{
	size_t	i;

	i = 0;
	//Iterar e libarar cada string
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	//Liberar array
	free(tab);
}

/*
	A funça para exibir mensagem de erro e encerra o programa
	@param cmd: Comando que causou o erro
	@return: Não retorna (encerra o programa)
*/
int	ft_command_error(char *cmd)
{
	// Concatena uma nova linha ao comando para exibição
	cmd = ft_strjoin(cmd, "\n");
	// Escreve a mensagem de erro no stderr
	write(2, "command not found: ", 20);
	write(2, cmd, ft_strlen(cmd));
	// Libera a memória do comando concatenado
	free(cmd);
	exit(127);
}
/*
	Funçao para obter o caminho completo do executável
	@param full_cmd: Array de strings com o comando e seus argumentos
	@param envp: Array de strings com as variáveis de ambiente
	@return: Caminho completo do executável ou NULL se não encontrado
*/
char	ft_get_path(char **full_cmd, char **envp)
{
	int		i;
	char	*path;
	char	*new;
	char	*cmd;
	char	**path_split;

	i = 0;
	//Encotrar variavel PATH
	path = ft_find_path(envp);

	if (path == NULL)
	{
		// Se PATH não é encontrada, retorna um erro
		new = ft_strdup(full_cmd[0]);
		(ft_command_error(new));
	}

	// Concatena "/" ao nome do comando
	cmd = ft_strjoin("/", full_cmd[0]);
	
	// Dividir variavel PATH em diretórios
	path_split = ft_split(path, ':');
	while (path_split[i] != NULL)
	{
		// Concatena o diretório com o comando
		path = ft_strjoin(path_split[i], cmd);
		
		// Verifica se o comando existe e é executável
		if (access(path, F_OK | X_OK) == 0)
		{
			return (free(cmd), ft_free_memory(path_split), path);
		}
		free(path);
		i++;
	}
	// Libera a memória e retorna NULL se o comando não for encontrado
	(free(cmd), ft_free_memory(path_split));
	return (NULL);
}






/*
	Função que cria um pipe, esperando um array[2] de inteiros 
	para armazenar dois descritores de arquivo (fd).
	- fd[0]: Usado para leitura do pipe.
	- fd[1]: Usado para escrita no pipe.
	Se ocorrer um erro na criação do pipe, uma mensagem de erro é exibida
	e o programa termina com um código de saída de falha.

void	create_pipe(int	*fd)
{
	if (pipe(fd) == -1)
	{
		perror("Error ao criar o pipe");
		exit(1);
	}
}
*/
/*
	 Função para fechar os descritores de arquivo criados pelo pipe.
	- Fecha fd[0], que é usado para leitura.
	- Fecha fd[1], que é usado para escrita.
	Essa função garante que ambos os descritores de arquivo sejam fechados
	corretamente para evitar vazamentos de recursos.

void	close_pipe(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}
*/

/*
	Função que redireciona a entrada padrão (stdin) para um arquivo.
	- file: Nome do arquivo a ser usado como entrada.
	1. Abre o arquivo no modo de leitura (O_RDONLY).
	Se ocorrer um erro ao abrir o arquivo, uma mensagem de erro é exibida
	e o programa termina com um código de saída de falha.

void	redir_input(const char *file)
{
	int	input_file;
	
	// Abre o arquivo de entrada no modo somente leitura
	input_file = open(file, O_RDONLY);
	if (input_file == -1)// Verifica se houve erro ao abrir o arquivo
	{
		perror("Erro ao abrir o arquivo de entrada");
		exit(1);
	}
	// Redireciona a entrada padrão (stdin) para o arquivo de entrada
	if (dup2(input_file, STDIN_FILENO) ==-1)// Verifica se houve erro ao redirecionar
	{
		perror("Erro ao redicionar a entrada padrao");
		close(input_file);// Fecha o arquivo de entrada em caso de erro
		exit(1);
	}
	// Fecha o descritor de arquivo do arquivo de entrada
	close(input_file);
}
*/
/*
	Função que redireciona a saída padrão (stdout) para um arquivo 
	especificado.
	- file: Nome do arquivo para o qual a saída padrão será redirecionada.
		1. Abre o arquivo no modo de escrita (O_WRONLY).
			- Cria o arquivo se ele não existir (O_CREAT).
			- Trunca o arquivo (zera o conteúdo) se ele já existir (O_TRUNC).
		2. Redireciona o descritor de saída padrão (STDOUT_FILENO) 
			para o descritor do arquivo aberto.
		3. Fecha o descritor do arquivo após o redirecionamento.
		- Exibe uma mensagem de erro caso o arquivo não possa ser aberto
		ou o redirecionamento falhe, encerrando o programa.

void redir_output(const char *file)
{
	int	output_file;

	output_file = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (output_file == -1)
	{
		perror("Erro ao abrir o arquivo de saída");
		exit(1);
	}
	if (dup2(output_file, STDOUT_FILENO) == -1)
	{
		perror("Erro ao redirecionar a saída padrão");
		close(output_file);
		exit(1);
	}
	close(output_file);
}
*/

/**
 * Função para executar um comando com seus argumentos
 	-cmd: Array de strings contendo o caminho do 
		comando e seus argumentos
	-env: Array de strings contendo as variáveis 
		de ambiente (pode ser NULL)
 * Esta função utiliza execve para substituir 
 	o processo atual pelo novo processo
 * Especificado em cmd[0]. Se a execução falhar, 
 	uma mensagem de erro será exibida
 * e a função retornará um valor 1.


int	exec_command(char **cmd, char **env)
{
	execve(cmd[0], cmd, env);
	perror("Erro ao executar comando");
	return 1;
}
 */
