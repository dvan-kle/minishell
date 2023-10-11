/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/22 15:32:12 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/10/09 21:30:43 by tijmendebru   ########   odam.nl         */
/*   Updated: 2023/10/10 12:15:28 by dvan-kle      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <stdio.h>
# include <limits.h>
# include <errno.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/signal.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include "builtins.h"
# include "env.h"
# include "exec.h"
# include "parser.h"
# include "tokenizer.h"
# include "heredoc.h"
# include <stdio.h>

t_cmd_table	*make_cmd_table(t_token *token_list, t_env_list *env_list);
void		free_token_list(t_token *token_list);
void		free_cmd_table(t_cmd_table *cmd_table);
void		free_env_list(t_env_list *env_list);
void		init_signals(void);
void		ignore_signals(void);
void		default_signals(void);

#endif