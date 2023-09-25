/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/18 14:56:53 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/09/25 20:22:46 by tijmendebru   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "env.h"
# include "tokenizer.h"

typedef struct s_redirect	t_redirect;

typedef struct s_redirect{
	t_tokentype	type;
	char		*file;
}t_redirect;

typedef struct s_cmd_table	t_cmd_table;

typedef struct s_cmd_table{
	char			**args;
	unsigned int	cmd_count;
	t_env_list		*env_list;
	t_redirect		*redirects;
	t_cmd_table		*next;
}t_cmd_table;

t_redirect	*redirect_add_back(t_token *token_lst, t_cmd_table *cmd_table);
void		print_redirects(t_redirect *redir_lst);
t_cmd_table	*cmd_add_back(t_cmd_table *cmd_table, t_token *to_be_added);
void		print_cmd_table(t_cmd_table *cmd_table);
int			arg_token_count(t_token *to_be_added);
int			allocate_cmd_table(t_cmd_table *cmd_table, t_token *lst);
bool		ft_isredirect(t_tokentype type);

#endif