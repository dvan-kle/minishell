/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/25 15:45:31 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/09/22 23:11:01 by tijmendebru   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "../libft/libft.h"
# include "env.h"
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
	APPEND_TOKEN,
	END_OF_CMD_TOKEN
}t_tokentype;

typedef struct token	t_token;

typedef struct token{
	t_tokentype	type;
	char		*value;
	bool		brackets;
	bool		new_cmd;
	int			whitespaces;
	bool		expand;
	t_env_list	*env_lst;
	t_token		*next;
}t_token;

t_token	*lexer(char *input, t_env_list *env_list);
t_token	*list_add_back(t_token *curr_list, t_token token_to_be_added);
t_token	*new_token(t_token token_to_be_added);
void	print_list(t_token *token_list);
void	free_list(t_token *token_list);
void	init_token(t_token *token, t_env_list *env_lst);
int		malloc_count(char *str, int i, char c);
void	assign_token(t_token *token, char *type, int i);
void	assign_minus(t_token *token, char *type, int i);
void	assign_bracket(t_token *token, char *type, int i, char bracket);
void	assign_pipe(t_token *token);
t_token	check_new_cmd(t_token *token);
t_token	handle_brackets(int i, char *input, t_token token);
t_token	handle_rest(int i, char *input, t_token token);
bool	ft_isredir(char c);
int		next_whitespace(char *input, int i);
int		update_input(t_token *token, char *input);
void	*ft_malloc(size_t size);
char	*assign_var(t_token *token, char *input, int i);
bool	find_key(t_token *token, char *key, char *input);
int		next_whitespace_and_bracket(char *input, int i);
int		next_whitespace_brackets(char *input, int i);

#endif