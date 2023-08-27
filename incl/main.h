/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/22 15:32:12 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/08/25 15:48:51 by tijmendebru   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <stdio.h>
# include "env.h"
# include "../libft/libft.h"
# include "parser.h"
# include "tokenizer.h"

void		env(t_env_list *env_list);
void		export(t_env_list *env_list, char *input);
t_token		*lexer(char *input);
t_cmd_table	*make_cmd_table(t_token	*token_list, t_env_list *env_list);
void		unset(t_env_list *env_list, char *input);
void		free_token_list(t_token *token_list);
void		free_cmd_table(t_cmd_table *cmd_table);
void		free_env_list(t_env_list *env_list);
void		run_sngl_cmd(t_cmd_table *cmd_table);
int	        cd(const char *path);

#endif