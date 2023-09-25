/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-kle <dvan-kle@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/23 13:42:56 by dvan-kle      #+#    #+#                 */
/*   Updated: 2023/09/25 20:23:16 by daniel        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "parser.h"

int	execute(t_cmd_table *cmd_table, t_env_list *env_list);
int	cd(const char *path);
void	pwd(void);
void    ignore_signals(void);
bool	execute_builtin(t_cmd_table *cmd_table, t_env_list *env_list);
void	ft_free(char **ptr);

#endif