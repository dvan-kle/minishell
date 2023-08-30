/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-kle <dvan-kle@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/23 13:42:56 by dvan-kle      #+#    #+#                 */
/*   Updated: 2023/08/30 19:19:18 by dvan-kle      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "parser.h"

int			execute(char **args);
void 		execute_pipeline(t_cmd_table *cmd_table, int pipe_count);
int			cd(const char *path);

#endif