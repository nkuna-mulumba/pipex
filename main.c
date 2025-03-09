/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcongolo <jcongolo@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-03 15:33:37 by jcongolo          #+#    #+#             */
/*   Updated: 2025-03-03 15:33:37 by jcongolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int		file_pipe[2];
	pid_t	id[2];
	int		status;

	if (argc != 5)
	{
		write(2, "Usage: ./pipex intfile cmd1 cmd2 outfile\n", 41);
		exit(1);
	}
	if (pipe(file_pipe) == -1)
	{
		perror("Error:");
		exit(1);
	}
	id[0] = ft_cmd1(argv, envp, file_pipe);
	id[1] = ft_cmd2(argv, envp, file_pipe, argc);
	close(file_pipe[0]);
	close(file_pipe[1]);
	waitpid(id[0], &status, 0);
	waitpid(id[1], &status, 0);
	exit(WEXITSTATUS(status));
	return (0);
}