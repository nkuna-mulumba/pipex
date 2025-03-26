/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_pipex_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcongolo <jcongolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 13:16:59 by jcongolo          #+#    #+#             */
/*   Updated: 2025/03/26 01:25:02 by jcongolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

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
	


