# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: tijmendebruine <tijmendebruine@student.      +#+                      #
#                                                    +#+                       #
#    Created: 2023/08/25 15:57:53 by tijmendebru   #+#    #+#                  #
#    Updated: 2023/10/13 12:08:26 by tde-brui      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #


.SILENT: all clean fclean re

NAME = minishell

LIBFT = libft/libft.a
LIBS = -lreadline

CC = cc
CC_FLAGS = -Wall -Wextra -Werror
SRC =   src/builtins/builtins.c src/builtins/builtins2.c src/builtins/env_list_fncs.c src/builtins/env_list_utils.c src/builtins/exit.c src/builtins/cd.c src/builtins/export.c \
        src/exec/exec.c src/exec/exec_utils.c src/exec/pipe.c src/exec/redirect_multi.c src/exec/redirect_single.c src/exec/errors.c src/exec/builtins.c \
        src/main/main.c src/main/input_error.c \
		    src/heredoc/heredoc_utils.c src/heredoc/heredoc.c \
        src/parsing/parser.c src/parsing/token_list_fncs.c src/parsing/tokenizer.c src/parsing/utils.c src/parsing/assign_token.c src/parsing/redirect.c src/parsing/cmd_table.c src/parsing/handle_token.c src/parsing/malloc.c src/parsing/utils2.c src/parsing/input_utils.c src/parsing/key.c\
		    src/signals/signals.c \

OBJ_DIR = obj/
OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

$(NAME): $(OBJ) $(LIBFT)
	@echo "\033[32mCompile minishell\033[0m"
	@$(CC) $(CC_FLAGS) $(OBJ) $(LIBFT) $(LIBS) -o $(NAME)
	@echo "\033[32mBuild complete\033[0m"
	
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
