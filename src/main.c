/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcongolo <jcongolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:33:37 by jcongolo          #+#    #+#             */
/*   Updated: 2025/03/19 11:36:53 by jcongolo         ###   ########.fr       */
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

/*
//Testar a funçao ft_exec_multiple_pipes()
int main(int argc, char **argv, char **env)
{
	if (argc < 5)
	{
		write(2 , "Use: ./pipex infile cmd1 cmd2 ... cmdn outfile\n", 48);
		return(1);
	}
	ft_exec_multiple_pipes(argc, argv, env);
	return (0);
}
*/


/*
testar funcionamento de ft_get_next_line
int main(int argc, char **argv)
{
	int	fd;
	char *line;
	if (argc != 2)
	{
		perror("Error:");
		return (1);
	}
	
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
        perror("Error opening file");
        return 1;
    }

    while ((line = ft_get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);// Libera a memória
    }

    close(fd);
    return 0;
}
*/

int main(int argc, char **argv, char **env)
{
	if(argc < 5)
	{
		write(2, "Usage: ./pipex infile cmd1 cmd2 outfile\n", 41);
		return (1);	
	}
	//Verificar se é "here_doc"
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		if (argc < 6)
		{
			write(2, "Usage: ./pipex here_doc LIMITADOR cmd1 cmd2 outfile\n", 52);
			return (1);
		}
		ft_here_doc(argv[2], argc, argv, env); //Chamar a funçao para 'here_doc'
	}
	else
	{
		ft_exec_multiple_pipes(argc, argv, env, 0);//Chamara a funçao para multiplos pipes
	}
	return (0);
}



