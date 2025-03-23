/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcongolo <jcongolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:33:37 by jcongolo          #+#    #+#             */
/*   Updated: 2025/03/23 15:07:30 by jcongolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
/*
int	main(int argc, char **argv, char **env)
{
	int		pipe_fd[2];// Descritores do pipe
	pid_t	id[2]; // IDs dos processos filhos
	int		process_status; // Status dos filhos
	
	if (argc != 5)
	{
		write(2, "Usage: ./pipex infile cmd1 cmd2 outfile\n", 41);
		exit(1);
	}
	if (pipe(pipe_fd) == -1)
	{
		perror("Error:");
		exit(1);
	}
	
	id[0] = ft_cmd1(argv, env, pipe_fd); // Executa cmd1
	
	id[1] = ft_cmd2(argv, env, pipe_fd, argc);// Executa cmd2
	
	close(pipe_fd[0]);// Fecha leitura do pipe
	close(pipe_fd[1]); // Fecha escrita do pipe
	waitpid(id[0], &process_status, 0);// Espera cmd1 terminar
	waitpid(id[1], &process_status, 0);
	exit(WEXITSTATUS(process_status));// Sai com o status de cmd2
	
	return (0);
}
*/

