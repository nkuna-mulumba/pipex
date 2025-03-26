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
    char *path;

    if (!s_cmd || !s_cmd[0])
	{
        write(2, "Pipex: command not found: \n", 28);
        exit(127);
    }

    // Verifica caminhos absolutos/relativos
    if ((s_cmd[0][0] == '/') || (ft_strncmp(s_cmd[0], "./", 2) == 0))
	{
        if (access(s_cmd[0], F_OK|X_OK) == 0)
        {
			return (ft_strdup(s_cmd[0]));	
		}
        ft_cmd_error(s_cmd[0]);
        ft_free_array(s_cmd);
        exit(127);
    }

    // Busca no PATH
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

	// Divide o comando em argumentos e verifica se é válido.
	if (!cmd || !*cmd || !(s_cmd = ft_split(cmd, ' ')))
	{
        write(2, "Pipex: Missing command: \n", 26);
        exit(127);
    }
	
	// Localiza o caminho completo do comando
	path = ft_check_and_locate_cmd(s_cmd, env);

	// Executa o comando localizado
	if (execve(path, s_cmd, env) == -1)
	{
        ft_cmd_error(s_cmd[0]);
        ft_free_array(s_cmd);
        free(path);
        exit(126);
    }
	// Libera memória
	ft_free_array(s_cmd);
	free(path);
}

/*
    Funçao para exibir mensagem de erro sobre o arquivo e encerra o programa.
    @param filename: Nome do arquivo relacionado ao erro.
    @return: Não retorna (termina com exit(1)).
*/
void	ft_file_error(char *filename)
{
    perror(filename);  // Exibe mensagem padrão de erro baseada no sistema.
    exit(1);           // Encerra o programa com código de erro.
}

/*
    Funçao que abre um arquivo para leitura ou escrita.
    @param filename: Nome do arquivo a ser aberto.
    @param mode: Modo de abertura (ex.: O_RDONLY ou O_WRONLY).
    @param is_output: Indica se é um arquivo de saída (1 para saída, 0 para entrada).
*/
int	ft_open_file(char *filename, int mode, int is_output) 
{
    int	fd;
    
	// Verifica se o nome do arquivo é válido
    if (!filename || !*filename)
	{
        write(2, "Pipex: invalid filename\n", 24);
        exit(1);
    }

    // Abre o arquivo de saída com permissões padrão
    if (is_output)
	{
        fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
        if (fd < 0)
		{
            ft_file_error(filename);
        }
        return (fd);
    }

    // Abre o arquivo de entrada no modo especificado
    fd = open(filename, mode);
    if (fd < 0)
	{
        ft_file_error(filename);
    }
    return (fd);
}


/*
    Função para redirecionar entrada e saída no processo filho.
    @param fd_in: Descritor de arquivo para entrada.
    @param fd_out: Descritor de arquivo para saída.
*/
void	ft_redirect_io(int fd_in, int fd_out)
{
    // Redireciona a entrada padrão para o descritor fornecido.
    if (dup2(fd_in, STDIN_FILENO) == -1)  // Verifica se dup2 teve sucesso.
    {
        perror("dup2 error (fd_in)");    // Exibe erro detalhado caso falhe.
        exit(1);                        // Encerra com código de erro.
    }

    // Redireciona a saída padrão para o descritor fornecido.
    if (dup2(fd_out, STDOUT_FILENO) == -1)  // Verifica se dup2 teve sucesso.
    {
        perror("dup2 error (fd_out)");   // Exibe erro detalhado caso falhe.
        exit(1);                        // Encerra com código de erro.
    }
}



/*
    Funçao para executa o 1º comando.
    Redireciona entrada do arquivo e saída para o pipe.
    @param argv: Argumentos passados ao programa.
    @param env: Variáveis de ambiente.
    @param file_pipe: Descritores do pipe.
    @return: PID do processo filho ou -1 em caso de erro.
*/
pid_t	ft_cmd1(char **argv, char **env, int *file_pipe) 
{
    pid_t	pid;
    int		fd;

	// Abre o arquivo de entrada para leitura
    fd = ft_open_file(argv[1], O_RDONLY, 0);
    if (fd < 0)
	{
        return (-1);
    }

	// Cria o processo filho
    pid = fork();
    if (pid == -1)
	{
        close(fd);
        perror("Pipex: fork");
        exit(1);
    }
	// No processo filho
    if (pid == 0)
	{
        ft_redirect_io(fd, file_pipe[1]);//Configura entrada e saída
        close(fd);// Fecha arquivo
        close(file_pipe[0]);//Fecha leitura do pipe
		close(file_pipe[1]);//Fecha escrita do pipe
        ft_exec_cmd_chek(argv[2], env);//Executa o comando
    }
	// No processo pai, fecha arquivo de entrada
    close(fd);
	// Retorna PID do filho
    return (pid);
}


/*
    Funçao para executar o 2º comando.
    Redireciona entrada do pipe e saída para o arquivo de saída.
    @param argv: Argumentos passados ao programa.
    @param env: Variáveis de ambiente.
    @param file_pipe: Descritores do pipe.
    @param argc: Número de argumentos.
    @return: PID do processo filho.
*/
pid_t	ft_cmd2(char **argv, char **env, int *file_pipe, int argc) 
{
    pid_t	pid;
    int		fd;

    pid = fork();
    if (pid == -1)
	{
        perror("pipex: fork");
        exit(1);
    }
    if (pid == 0)
	{
        // Abre o arquivo de saída
        fd = open(argv[argc-1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd < 0)
		{
            ft_file_error(argv[argc-1]);// Erro ao abrir arquivo de saída
        }
		// Redireciona entrada do pipe e saída para o arquivo
        ft_redirect_io(file_pipe[0], fd);
		//Fecha descritores no processo filho
        close(fd);
        close(file_pipe[0]);
		close(file_pipe[1]);
		// Executa o comando
        ft_exec_cmd_chek(argv[argc-2], env);
    }
    return (pid);
}
