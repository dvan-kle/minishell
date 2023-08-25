# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: tijmendebruine <tijmendebruine@student.      +#+                      #
#                                                    +#+                       #
#    Created: 2023/08/25 15:41:30 by tijmendebru   #+#    #+#                  #
#    Updated: 2023/08/25 15:51:44 by tijmendebru   ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = minishell


LIBFT = libft/libft.a
LIBS = -lreadline

CC = gcc
CC_FLAGS = -Wall -Wextra -fsanitize=address
SRC =    src/builtins/builtins.c src/builtins/builtins2.c src/builtins/env_list_fncs.c \
        src/exec/folders.c src/exec/exec.c src/exec/pipe.c \
        src/main/main.c \
        src/parsing/parser.c src/parsing/token_list_fncs.c src/parsing/tokenizer.c src/parsing/utils.c src/parsing/assign_token.c

OBJ_DIR = obj/
OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

all: $(NAME)

.SILENT:

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CC_FLAGS) $(OBJ) $(LIBFT) $(LIBS) -o $(NAME)

$(OBJ_DIR)%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CC_FLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) all -C libft

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) clean -C libft


fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C libft

re: fclean all