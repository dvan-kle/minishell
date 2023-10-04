/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/22 15:32:12 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/10/01 22:39:15 by daniel        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <stdio.h>
# include "../libft/libft.h"
# include "env.h"
# include "parser.h"
# include "tokenizer.h"
# include "exec.h"
# include "builtins.h"


t_cmd_table	*make_cmd_table(t_token	*token_list, t_env_list *env_list);
void		free_token_list(t_token *token_list);
void		free_cmd_table(t_cmd_table *cmd_table);
void		free_env_list(t_env_list *env_list);
void		init_signals(void);
void	    ignore_signals(void);

#endif