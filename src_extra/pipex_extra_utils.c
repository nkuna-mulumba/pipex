/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_extra_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcongolo <jcongolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 11:39:26 by jcongolo          #+#    #+#             */
/*   Updated: 2025/03/23 12:58:10 by jcongolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

/* 
 Função: ft_extract_line
 Propósito: Extrai a próxima linha do remainder.
 Uso: Esta função é usada para obter uma linha completa de texto armazenado em remainder.
*/
static char	*ft_extract_line(char **remainder)
{
    char *newline_pos;
    char *line;
    size_t len;
    char *temp;

    if (!remainder || !*remainder)
        return (NULL); // Retorna NULL se remainder for NULL ou vazio
    newline_pos = ft_strchr(*remainder, '\n'); // Procura o caractere de nova linha
    if (!newline_pos)
    {
        line = ft_strdup(*remainder); // Duplica o remainder inteiro se não houver nova linha
        free(*remainder); // Libera a memória de remainder
        *remainder = NULL; // Define remainder como NULL
        return (line); // Retorna a linha duplicada
    }
    len = newline_pos - *remainder + 1; // Calcula o comprimento da linha incluindo \n
    line = malloc((len + 1) * sizeof(char)); // Aloca memória para a linha
    if (!line)
        return (NULL); // Retorna NULL se a alocação falhar
    ft_strlcpy(line, *remainder, len + 1); // Copia a linha para a memória alocada
    temp = ft_strdup(newline_pos + 1); // Duplica o restante após \n
    free(*remainder); // Libera a memória de remainder
    *remainder = temp; // Atualiza remainder para apontar para o restante
    return (line); // Retorna a linha extraída
}

/*
	Função: ft_read_and_update_remainder
	Propósito: Lê dados do arquivo e atualiza o conteúdo de remainder até encontrar uma nova linha.
	Uso: Esta função é usada para ler novos dados do arquivo e adicioná-los ao conteúdo existente em remainder, até que uma nova linha seja encontrada.
*/
static int ft_read_and_update_remainder(int fd, char **remainder)
{
    char *buffer;
    char *temp;
    ssize_t bytes_read;

    buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char)); // Aloca memória para o buffer
    if (!buffer)
        return (-1); // Retorna -1 se a alocação falhar

    bytes_read = 1; // Inicializa bytes_read com 1 para entrar no loop
    while (bytes_read && (*remainder == NULL || !ft_strchr(*remainder, '\n'))) // Continua lendo até encontrar uma nova linha
    {
        bytes_read = read(fd, buffer, BUFFER_SIZE); // Lê do arquivo para o buffer
        if (bytes_read <= 0)
        {
            free(buffer); // Libera o buffer se a leitura falhar ou chegar ao fim do arquivo
            return (bytes_read); // Retorna o número de bytes lidos (ou erro)
        }
        buffer[bytes_read] = '\0'; // Adiciona o terminador nulo ao buffer

        if (*remainder == NULL)
            temp = ft_strdup(buffer); // Se remainder for NULL, duplica o buffer
        else
            temp = ft_strjoin(*remainder, buffer); // Caso contrário, concatena remainder e buffer

		if (!temp)
        {
            free(buffer); // Libera o buffer em caso de falha
            return (-1); // Retorna -1 se a junção falhar
        }
        free(*remainder); // Libera o antigo remainder
        *remainder = temp; // Atualiza remainder para a nova string combinada
    }
    free(buffer); // Libera o buffer após sair do loop
    return (bytes_read); // Retorna o número de bytes lidos
}

/*
 Função: get_next_line
 Propósito: Obtém a próxima linha do arquivo.
 Uso: Esta função é a função principal que chama `ft_read_and_update_remainder` para ler 
 dados e `ft_extract_line` para extrair a próxima linha.
*/
char *ft_get_next_line(int fd)
{
    static char *remainder; // Variável estática para armazenar os dados restantes
    char *line;
    int result; // Variável para armazenar o resultado da operação de leitura

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL); // Retorna NULL para descritor de arquivo inválido ou tamanho de buffer inválido

    result = ft_read_and_update_remainder(fd, &remainder); // Lê e atualiza remainder

    if ((result <= 0) && (!remainder || *remainder == '\0'))
    {
        free(remainder); // Libera remainder se o fim do arquivo for alcançado
        remainder = NULL;
        return (NULL); // Retorna NULL no final do arquivo
    }

    line = ft_extract_line(&remainder); // Extrai a linha do remainder
    return (line); // Retorna a linha extraída
}	


