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
