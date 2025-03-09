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
	// Concatena uma nova linha ao comando para exibição
	cmd = ft_strjoin(cmd, "\n");
	// Escreve a mensagem de erro no stderr(2)
	write(2, "Invalid command: ", 17);
	write(2, cmd, ft_strlen(cmd));
	// Libera a memória do comando concatenado
	free(cmd);
	exit(127);//indicando que o comando não foi encontrado
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
	@param full_cmd: Array de strings com o comando e seus argumentos
	@param env: Array de strings com as variáveis de ambiente
	@return: Caminho completo do executável ou NULL se não encontrado
*/
char	*ft_locate_cmd(char **s_cmd, char **env)
{
	int		i;
	char	*path;
	char	*new;
	char	*cmd;
	char	**path_split;

	//Encotrar variavel PATH
	path = ft_get_path_variable(env);
	if (path == NULL)
	{
		// Se PATH não é encontrada, retorna um erro
		new = ft_strdup(s_cmd[0]);
		ft_cmd_error(new);
	}
	
	// Concatena "/" ao nome do comando
	cmd = ft_strjoin("/", s_cmd[0]);
	
	// Dividir variavel PATH em diretórios
	path_split = ft_split(path, ':');
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
	free(cmd);
	ft_free_array(path_split);
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

	// Verificar se o comando é um caminho absoluto iniciado com "/"
	if ((access(s_cmd[0], F_OK | X_OK) == 0) && (s_cmd[0][0] == '/'))
	{
		// Executar o comando se for um caminho absoluto
		if (execve(s_cmd[0], s_cmd, env) == -1)//Caso falhar
		{
			ft_cmd_error(s_cmd[0]);
			ft_free_array(s_cmd);
		}
	}

	// Verificar se o comando é um caminho relativo iniciado com "./"
	if ((access(s_cmd[0], F_OK | X_OK) == 0) && (ft_strncmp(s_cmd[0], "./", 2)))
	{
		// Executa o comando se for um caminho relativo
		if (execve(s_cmd[0], s_cmd, env) == -1)//Caso falhar
		{
			ft_cmd_error(s_cmd[0]);
			ft_free_array(s_cmd);
		}
	}
	// Se o comando não é acessible e contem "/"
	else if (access(s_cmd[0], F_OK | X_OK) != 0 && ft_strchr(s_cmd[0], '/'))
	{
		ft_cmd_error(s_cmd[0]);
		ft_free_array(s_cmd);
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
		}
		ft_free_array(s_cmd);
		free(path);
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
