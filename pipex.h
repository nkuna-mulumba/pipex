/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcongolo <jcongolo@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-03 14:28:23 by jcongolo          #+#    #+#             */
/*   Updated: 2025-03-03 14:28:23 by jcongolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

//Adicionar biblioteca "libft" no projecto
# include "libft/libft.h"

/*
	DECLARAÇAO DAS FUNÇOES:
*/
//Funçao para criar um "pipe"
void	create_pipe(int *fd);
//Funçao para fechar os fd criado por defeito com "pipe"
void	close_pipe(int *fd);
//Funçao para redicionar a entrada padrao (stdin) para fd
void	redir_input(const char *file);


#endif

// void create_pipe(int *fd);1
// void close_pipe(int *fd);2
// void redir_input(const char *file); 3
// int exec_command(char **cmd, char **env);
// void redir_output(const char *file);
// void execute_pipeline(const char *input_file, const char *output_file, char **cmd1, char **cmd2, char **envp);