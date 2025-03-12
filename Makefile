# Nome do executavel final
NAME = pipex

# Arquivo fonte do projecto
SRC_DIR = src

# Arquivo fonte do projecto
SRC = $(SRC_DIR)/pipex_utils.c\
	$(SRC_DIR)/pipex.c\
	$(SRC_DIR)/main.c
OBJ = $(SRC:.c=.o)

# Compilador a ser usado e Flags do compilador
CC = cc
FLAGS = -Wall -Wextra -Werror #-g

# Diretório da bibliotecas LIBFT
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

# Regra padrão para compilar o executável
all: $(LIBFT) $(NAME)

# Regras para criar o executável a partir dos objetos
$(NAME): $(OBJ)
	$(CC) $(FLAGS) -o $(NAME) $(OBJ) $(LIBFT)

# Regras para compilar as bibliotecas LIBFT
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# Regra para compilar os arquivos .c em .o
%.o: %.c
	$(CC) $(FLAGS) -I$(LIBFT_DIR) -c $< -o $@

# Regra para compilar os arquivos .c em .o
clean:
	rm -f $(OBJ)
	$(MAKE) -C $(LIBFT_DIR) clean

# Regra para limpar todos os arquivos gerados, incluindo o executável
fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

# Regra para reconstruir tudo do zero
re: fclean all

# Declarar alvos que não são arquivos para evitar conflitos
.PHONY: all clean fclean re
