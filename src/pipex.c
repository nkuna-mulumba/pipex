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
	A funçao que verifica e localiza o comando para execução.
	-> s_cmd: Array de strings resultante da divisão do comando.
	-> env: Array com as variáveis de ambiente do sistema.
	-> return: Caminho completo do comando (absoluto, relativo ou
		encontrado no PATH).
	Se o comando for inválido ou não encontrado, a função termina com `exit`
*/
static char	*ft_check_and_locate_cmd(char **s_cmd, char **env)
{
	char	*path;

	if (!s_cmd || !s_cmd[0])
	{
		write(2, "Pipex: command not found: \n", 28);
		exit(127);
	}
	// Verifica caminhos absolutos/relativos
	if ((s_cmd[0][0] == '/') || (ft_strncmp(s_cmd[0], "./", 2) == 0))
	{
		if (access(s_cmd[0], F_OK | X_OK) == 0)
			return (ft_strdup(s_cmd[0]));
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
	return (path);
}

/*
	Funçao que verifica, localiza e executa um comando fornecido.
	-> cmd: O comando a ser executado.
	-> env: Array com as variáveis de ambiente do sistema.
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
	Funçao que abre um arquivo para leitura ou escrita.
	-> filename: Nome do arquivo a ser aberto.
	-> mode: Modo de abertura (ex.: O_RDONLY ou O_WRONLY).
	-> is_output: Indica se é um arquivo de saída (1 para saída,
	0 para entrada).
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
	-> fd_in: Descritor de arquivo para entrada.
	-> fd_out: Descritor de arquivo para saída.
*/
void	ft_redirect_io(int fd_in, int fd_out)
{
	// Redireciona a entrada padrão para o descritor fornecido.
	if (dup2(fd_in, STDIN_FILENO) == -1) // Verifica se dup2 teve sucesso.
	{
		perror("dup2 error (fd_in)"); // Exibe erro detalhado caso falhe.
		exit(1);// Encerra com código de erro.
	}
	// Redireciona a saída padrão para o descritor fornecido.
	if (dup2(fd_out, STDOUT_FILENO) == -1) // Verifica se dup2 teve sucesso.
	{
		perror("dup2 error (fd_out)"); // Exibe erro detalhado caso falhe.
		exit(1);// Encerra com código de erro.
	}
}
