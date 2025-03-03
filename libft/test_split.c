/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcongolo <jcongolo@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-26 16:24:15 by jcongolo          #+#    #+#             */
/*   Updated: 2025-02-26 16:24:15 by jcongolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
void print_and_free(char **result)
{
    if (!result)
    {
        printf("Retornou NULL\n");
        return;
    }

    int i = 0;
    while (result[i])
    {
        printf("[%s]\n", result[i]);
        i++;
    }
    
    ft_freememoria(result, i);
    printf("Memória liberada corretamente!\n");
}

int main()
{
    char **result;

    printf("Teste 1 (string vazia):\n");
    result = ft_split("", ' ');
    print_and_free(result);

    printf("\nTeste 2 (apenas delimitadores):\n");
    result = ft_split("      ", ' ');
    print_and_free(result);

    printf("\nTeste 3 (texto normal):\n");
    result = ft_split("Eu sou Mangop", ' ');
    print_and_free(result);

    printf("\nTeste 4 (múltiplos espaços entre palavras):\n");
    result = ft_split("  Eu   sou   Mangop  ", ' ');
    print_and_free(result);

    printf("\nTeste 5 (delimitadores no início e fim):\n");
    result = ft_split("   Eu sou Mangop   ", ' ');
    print_and_free(result);

    return 0;
}
*/