/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/25 15:45:31 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/08/30 14:38:24 by tde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "../libft/libft.h"
# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>

typedef enum token_type{
	CMD_TOKEN,
	ARGUMENT_TOKEN,
	INPUT_REDIRECT_TOKEN,
	OUTPUT_REDIRECT_TOKEN,
	PIPE_TOKEN,
	READ_INPUT_TOKEN,
	OUTPUT_REDIRECT_APPEND_TOKEN,
	END_OF_CMD_TOKEN
}t_tokentype;

typedef struct token	t_token;

typedef struct token{
	t_tokentype	type;
	char		*value;
	bool		brackets;
	bool		new_cmd;
	int			whitespaces;
	t_token		*next;
}t_token;

t_token	*lexer(char *input);
t_token	*list_add_back(t_token *curr_list, t_token token_to_be_added);
t_token	*new_token(t_token token_to_be_added);
void	print_list(t_token *token_list);
void	free_list(t_token *token_list);
void	init_token(t_token *token);
int		malloc_count(char *str, int i, char c);
void	assign_token(t_token *token, char *type, int i);
int		assign_minus(t_token *token, char *type, int i);
int		assign_bracket(t_token *token, char *type, int i, char bracket);
void	assign_pipe(t_token *token);
t_token	check_new_cmd(t_token *token);

#endif