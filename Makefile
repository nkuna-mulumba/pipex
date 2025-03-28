
# Nome dos executáveis
NAME = pipex
BONUS_NAME = pipex_bonus

# Diretórios de fontes
SRC_DIR = src
SRC_EXTRA_DIR = src_extra
INCLUDE_DIR = include

# Arquivos fontes para a parte obrigatória e bônus
SRC = $(SRC_DIR)/pipex_utils.c\
	$(SRC_DIR)/pipex_error.c\
	$(SRC_DIR)/pipex.c\
	$(SRC_DIR)/main_pipex.c

SRC_BONUS = $(SRC_DIR)/pipex_utils.c\
	$(SRC_DIR)/pipex_error.c\
	$(SRC_DIR)/pipex.c\
	$(SRC_EXTRA_DIR)/pipex_extra_utils.c\
	$(SRC_EXTRA_DIR)/pipex_extra.c\
	$(SRC_EXTRA_DIR)/main_pipex_bonus.c

OBJ = $(SRC:.c=.o)
OBJ_BONUS = $(SRC_BONUS:.c=.o)

# Compilador e flags
CC = cc
FLAGS = -Wall -Wextra -Werror -I$(INCLUDE_DIR)

# Diretório da LIBFT
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

# Regras para compilar o executável principal e o bônus
all: $(LIBFT) $(NAME)

bonus: $(LIBFT) $(BONUS_NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) -o $(NAME) $(OBJ) $(LIBFT)

$(BONUS_NAME): $(OBJ_BONUS)
	$(CC) $(FLAGS) -o $(BONUS_NAME) $(OBJ_BONUS) $(LIBFT)

# Regra para compilar os arquivos .c em .o
%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

# Regra para compilar a LIBFT
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -f $(OBJ) $(OBJ_BONUS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all
re_bonus: fclean bonus

# Marcar alvos que não são arquivos
.PHONY: all bonus clean fclean re bonus_re