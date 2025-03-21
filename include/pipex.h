/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcongolo <jcongolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:28:23 by jcongolo          #+#    #+#             */
/*   Updated: 2025/03/19 11:45:02 by jcongolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

//Adicionar biblioteca "libft" no projecto
# include "../libft/libft.h"

/*
	DECLARAÇAO DAS FUNÇOES:
*/
//Funçao para fechar fd de arquivos do pipe, se falhar exibe erro
void	ft_pipe_error(int *fd, char *file);
//Funçao para encontrar a variavel de ambiente PATH
char	*ft_get_path_variable(char **env);
//Funçao para liberar memoria de cada string
void	ft_free_array(char **array);
//Funçao para exibir a mensagem de erro e encerrar programa
int		ft_cmd_error(char *cmd);
//Funçao para verificar se argumento é vazia ou contem espaço
void	ft_empty(char *cmd);
//Funçao para encontrar caminho completo do executavel
char	*ft_locate_cmd(char **cmd_s, char **env);
//Funçao para verificar e executar comandos
void	ft_exec_cmd_chek(char *cmd, char **envp);
//Funçao para executar 1º comando e redicionar entrada e saida no pipe
pid_t	ft_cmd1(char **argv, char **env, int *file_pipe);
//Funçao para executar 2º comando e redicionar entrada no pipe e saida para arquivo
pid_t	ft_cmd2(char **argv, char **env, int *file_pipe, int argc);

/* ##PARTE EXTRAS PARA SEQUENCIAS DE COMANDOS E PIPES ### */
//Funçao para executar múltiplos comandos conectados por pipes
void    ft_exec_multiple_pipes(int argc, char **argv, char **env, int in);
//Inicio do segundo bloco (BUFFER_SIZE)
# ifndef BUFFER_SIZE
#	define BUFFER_SIZE 1024 //Buffer para leitura
# endif // Fim do segundo bloco (BUFFER_SIZE)
char *ft_get_next_line(int fd);

//Funçao para 
void    ft_here_doc(char *limiter, int argc, char **argv, char **env);

#endif