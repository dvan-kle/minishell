/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-kle <dvan-kle@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/23 13:42:56 by dvan-kle      #+#    #+#                 */
/*   Updated: 2023/08/25 16:49:07 by danielvankl   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "parser.h"

int			execute(char **args);
void		test_execute(t_cmd_table *cmd_table, int pipe_count);
void	    test_num_exec(int num, t_cmd_table *cmd_table);
void		test_execute_single_cmd(t_cmd_table *cmd_table);
void		test_execute_single_pipe(t_cmd_table *cmd_table);
static char	**get_folders(void);
int			cd(const char *path);

#endif