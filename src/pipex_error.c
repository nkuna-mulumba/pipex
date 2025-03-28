/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcongolo <jcongolo@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-28 16:18:00 by jcongolo          #+#    #+#             */
/*   Updated: 2025-03-28 16:18:00 by jcongolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

/*
	Funçao para exibir mensagem de erro e
	encerra o programa em caso de nao encontrar cmd
	-> cmd: Comando que causou o erro
	-> return: Não retorna (encerra o programa)
*/
int	ft_cmd_error(char *cmd)
{
	write(2, "Pipex invalid command: ", 24); // Mensagem de erro no stderr(2)
	write(2, cmd, ft_strlen(cmd));
	write(2, "\n", 1);
	return (0);
}

/*
	Funçao para exibir mensagem de erro sobre o arquivo e encerra o programa.
	-> filename: Nome do arquivo relacionado ao erro.
	-> return: Não retorna (termina com exit(1)).
*/
void	ft_file_error(char *filename)
{
	perror(filename); // Exibe mensagem padrão de erro baseada no sistema.
	exit(1);// Encerra o programa com código de erro.
}
