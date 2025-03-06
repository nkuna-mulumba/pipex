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
//Funçao para encontrar a variavel de ambiente PATH
char	*ft_find_path(char **envp);
//Funçao para liberar memoria de cada string
void	ft_free_memory(char **tab);
//Funçao para exibir a mensagem de erro e encerrar programa
int	ft_command_error(char *cmd);

//Funçao para criar um "pipe"
// void	create_pipe(int *fd);
//Funçao para fechar os fd criado por defeito com "pipe"
//void	close_pipe(int *fd);
//Funçao para redicionar a entrada padrao (stdin) para fd
//void	redir_input(const char *file);
//Funçao para redicionar a saida padrao (stdout) para fd
//void	redir_output(const char *file);
//Funçao para executar comando com seus argumentos
//void	exec_command(const char *cmd);
//int exec_command(char **cmd, char **env);


#endif
