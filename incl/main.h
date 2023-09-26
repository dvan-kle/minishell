/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/22 15:32:12 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/09/26 11:26:10 by tijmendebru   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <stdio.h>
# include "env.h"
# include "../libft/libft.h"
# include "parser.h"
# include "tokenizer.h"
# include "exec.h"
# include "pipes.h"
# include "redirect.h"

void		env(t_env_list *env_list);
void		export(t_env_list *env_list, char *input);
t_cmd_table	*make_cmd_table(t_token	*token_list, t_env_list *env_list);
void		unset(t_env_list *env_list, char *input);
void		free_token_list(t_token *token_list);
void		free_cmd_table(t_cmd_table *cmd_table);
void		free_env_list(t_env_list *env_list);
void		run_sngl_cmd(t_cmd_table *cmd_table);
int			cd(const char *path);
void		init_signals(void);
void		ft_exit(t_cmd_table *cmd_table);
void		execute_error(char *cmd);
void		redirect_error(char *filename);
void	    echo(t_cmd_table	*cmd_table);

#endif