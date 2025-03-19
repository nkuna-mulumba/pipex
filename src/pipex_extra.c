/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_extra.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcongolo <jcongolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 17:02:35 by jcongolo          #+#    #+#             */
/*   Updated: 2025/03/19 14:19:40 by jcongolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

/*
    A funçao para executa múltiplos comandos conectados por pipes.
        Redireciona entrada do 1º comando para o arquivo de entrada (argv[1]) 
        e a saída do último comando para o arquivo de saída
        (argv[argc - 1]). Comandos intermediários recebem a saída do comando 
        anterior como entrada.
    Parâmetros:
        - argc: Número de argumentos.
        - argv: argv[1] = arquivo de entrada, argv[2..argc - 2] = comandos, 
            argv[argc - 1] = arquivo de saída.
        - env: Variáveis de ambiente.
    Comportamento:
        - Abre o arquivo de entrada.
        - Para cada comando intermediário:
            - Cria pipe e processo filho.
            - No filho: redireciona entrada/saída e executa o comando.
            - No pai: fecha escrita do pipe e atualiza entrada para o próximo comando.
        - Para o último comando:
            - Abre o arquivo de saída.
            - Cria processo filho para redirecionar entrada/saída e executar o comando.
            - No pai: fecha descritores e espera processos filhos terminarem.
    Retorno:
        Não retorna valor. Executa comandos e redireciona entradas/saídas.
*/
void    ft_exec_multiple_pipes(int argc, char **argv, char **env)
{
    int     fd_in;
    int     fd_out;
    int     i;
    int     pipe_fd[2];
    pid_t   pid; 
    
    fd_in = open(argv[1], O_RDONLY);//Abrir o arquivo de entrada
    // if (fd_in < 0)//se falhar de abrir o arquivo
        //perror("Error: open infile");

    i = 2;//primeiro comando
    while (i < argc - 2)// Loop para comandos intermediarios
    {
        if (pipe(pipe_fd) == -1)//Criar um pipe
            perror("Error: pipe");
            
        pid = fork(); //criar um processo
        if (pid == -1)
            perror("Error: fork");//Se falhar

        if (pid == 0)//Processo filho
        {
            close(pipe_fd[0]);//Fechar a leitura do pipe no processo filho
            dup2(fd_in, STDIN_FILENO);//Redicionar a entrada
            dup2(pipe_fd[1], STDOUT_FILENO);//Redicionar a saida para "pipe"
            close(pipe_fd[1]);// Fechar a escritura do pipe apos dup2
            ft_exec_cmd_chek(argv[i], env);//Executar o comando
        }
        else //Processo Pai
        {            
            close(pipe_fd[1]); //Fechar a escrita do pipe no processo pai
            close(fd_in);//Fechar o arquivo de entrada anterior
            fd_in = pipe_fd[0];//A entrada do proximo comando sera a saida do pipe atual
        }
        i++;
    }
    //Ultimo comando
    fd_out = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0744);//Abre o arquivo de saida
    if (fd_out < 0)
        perror("Error: open outfile");

    pid = fork();//Criar processos filho para ultimo comando
    if (pid == -1)
        perror("Error: fork");
    if (pid == 0)
    {
        dup2(fd_in, STDIN_FILENO); //Redicionar entrada do pipe
        dup2(fd_out, STDOUT_FILENO); //Redicionar saida para arquivo
        close(fd_in);//Fechar entrada do pipe
        close(fd_out);//Fechar arquivo de saida apos dup2
        ft_exec_cmd_chek(argv[argc - 2], env);//Executar ultimo comando       
    }
    else //Processo pai
    {
        close(fd_in);//Fechar entrada do pipe
        close(fd_out);//Fechar arquivo de saida
        while (wait(NULL) > 0);//Espera todos processos filhos terminarem
    }
}

/*
    Função para construir a linha a partir do buffer
*/
static char *ft_build_line(char *line, char *buffer, int *pos)
{
    int     line_size; // Tamanho da linha (local à função)
    char    *new_line;

    line_size = 0;
    if (line) // Se a linha já existir, calcule seu tamanho
        line_size = ft_strlen(line);

    while (buffer[*pos] != '\0' && buffer[*pos] != '\n') // Percorrer o buffer até encontrar uma nova linha
    {
        //Realocar memoria
        new_line = realloc(line, line_size + 2);//+2 para o novo caractere e '\0'
        if (!new_line)
        {
            free(line);// Liberar memória previamente alocada
            return (NULL);
        }
        line = new_line;
        line[line_size] = buffer[*pos];// Adicionar caractere ao final da linha
        line_size++; // Incrementar o tamanho da linha
        (*pos)++; // Avançar a posição no buffer
    }

    if (buffer[*pos] == '\n') // Se encontrar uma nova linha
    {
        new_line = realloc(line, line_size + 2);// +2 para '\n' e '\0'
        if (!new_line)
        {
            free(line);// Liberar memória previamente alocada
            return (NULL);
        }
        line = new_line;
        line[line_size] = '\n';// Adicionar o caractere de nova linha
        line[line_size + 1] = '\0'; // Finalizar a string
        (*pos)++; // Avançar a posição após a nova linha
    }

    return line; // Retornar a linha construída
}



// Função principal para ler uma linha do arquivo
char    *ft_get_next_line(int fd)
{
    static int  pos = 0;              // Posição atual no buffer
    static int  bytes_read = 0;       // Número de bytes lidos na última leitura
    static char buffer[BUFFER_SIZE]; // Buffer estático para armazenar dados lidos
    char        *line;               // Linha a ser retornada

    line = NULL;
    while (1)
    {
        if (pos >= bytes_read) // Se o buffer estiver vazio, leia mais dados
        {
            bytes_read = read(fd, buffer, BUFFER_SIZE);
            pos = 0;
            if (bytes_read < 0)
            {
                free(line);
                perror("Error reading file");
                return (NULL);
            }
            if (bytes_read == 0)// EOF (fim de arquivo)
            {
                if (line)// Retornar qualquer linha restante
                    return (line);
                return (NULL);// Nenhuma linha restante, retornar NULL
            }
        }
        //Construir a linha usando o buffer
        line = ft_build_line(line, buffer, &pos); // Construir a linha
        if (!line)
            return (NULL);
        //Se a linha estiver completa (terminar com '\n'), retornar
        if (line[ft_strlen(line) - 1] == '\n') // Se a linha estiver completa
            return line;
    }
}



/*
** ft_here_doc:
** - Lê entrada interativa até o LIMITADOR ser digitado.
** - Escreve o conteúdo coletado em um pipe.
** - Redireciona STDIN para esse pipe e chama ft_exec_multiple_pipes para
**   executar os comandos, ignorando os dois primeiros argumentos ("here_doc" e LIMITADOR).
*/
void    ft_here_doc(char *limiter, int argc, char **argv, char **env)
{
    int     fd[2];
    pid_t   pid;
    char    *line;
    char    *limiter_with_newline;
    
    limiter_with_newline = ft_strjoin(limiter, "\n");
    if (!limiter_with_newline)
    {
        perror("Error: malloc");
        exit(1);
    }
    
    if (pipe(fd) == -1)// Criar um pipe
        perror("Error: pipe");

    pid = fork();//Criar processo filho
    if(pid == -1)
        perror("Error: fork");

    if (pid == 0)//Processo filho
    {
        close(fd[0]);//Fechar leitura do pipe no processo filho
        while (1)
        {
            line = ft_get_next_line(STDIN_FILENO);//Ler entrada no usuario
            if (!line || ft_strcmp(line, limiter_with_newline) == 0) //Verificar o limitador
            {
                break;
            }
            
            write(fd[1], line, ft_strlen(line));//Escrever no pipe
            free(line);//Liberar a memoria alocada a linha
        }
        //###
        if (line)
        {
            free(line); //Liberar a ultima linha lida
        }
        
        close(fd[1]);//Fechar escrita do pipe
        free(limiter_with_newline);//Liberar o limitador com '\n'
        exit(0);//Terminar processo filho
    }
    else //Processo Pai
    {
        close(fd[1]);//Fechar escrita do pipe no processo do pai
        dup2(fd[0], STDIN_FILENO);//Redicionar entrada para o pipe 
        close(fd[0]);//Fechar leitura do pipe
        wait(NULL);//Esperar processo filho terminar
        ft_exec_multiple_pipes(argc - 2, argv + 2, env);//Executar comandos
        free(limiter_with_newline); // Liberar o limitador com '\n'
    }
}
