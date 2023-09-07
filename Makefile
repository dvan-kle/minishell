# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: tijmendebruine <tijmendebruine@student.      +#+                      #
#                                                    +#+                       #
#    Created: 2023/08/25 15:57:53 by tijmendebru   #+#    #+#                  #
#    Updated: 2023/09/07 14:53:48 by dvan-kle      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #


.SILENT: all clean fclean re

NAME = minishell

LIBFT = libft/libft.a
LIBS = -lreadline

CC = gcc
CC_FLAGS = -Wall -Wextra
SRC =    src/builtins/builtins.c src/builtins/builtins2.c src/builtins/env_list_fncs.c \
        src/exec/folders.c src/exec/exec.c src/exec/pipe.c src/exec/redirect.c \
        src/main/main.c \
        src/parsing/parser.c src/parsing/token_list_fncs.c src/parsing/tokenizer.c src/parsing/utils.c src/parsing/assign_token.c src/parsing/redirect.c src/parsing/cmd_table.c src/parsing/utils_malloc.c \
		
OBJ_DIR = obj/
OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

$(NAME): $(OBJ) $(LIBFT)
	@echo "\033[32mCompile minishell\033[0m"
	@$(CC) $(CC_FLAGS) $(OBJ) $(LIBFT) $(LIBS) -o $(NAME)
	@echo "\033[32mBuild complete\033[0m"
	@echo  "\033[31m___  ___  ___  _  __ ___   ___  _  _  ___  _     _    \033[0m"
	@echo  "\033[31m| __|| _ \|_ _|| |/ // _ \ / __|| || || __|| |   | |   \033[0m"
	@echo  "\033[31m| _| |   / | | | ' <| (_) |\__ \| __ || _| | |__ | |__ \033[0m"
	@echo  "\033[31m|_|  |_|_\|___||_|\_\\___/ |___/|_||_||___||____||____|\033[0m"

	
$(OBJ_DIR)%.o: %.c
	@echo "\033[32mCompiling Objects\033[0m"
	@mkdir -p $(dir $@)
	@$(CC) $(CC_FLAGS) -c $< -o $@

$(LIBFT):
	@echo "\033[32mBuilding Libft\033[0m"
	@$(MAKE) all -C libft

all: $(NAME)

clean:
	@echo "\033[32mClean\033[0m"
	@rm -rf $(OBJ_DIR)
	@$(MAKE) clean -C libft

fclean: clean
	@echo "\033[32mRun fclean\033[0m"
	@rm -f $(NAME)
	@$(MAKE) fclean -C libft

re: fclean all
