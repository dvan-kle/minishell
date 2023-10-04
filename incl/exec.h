/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-kle <dvan-kle@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/23 13:42:56 by dvan-kle      #+#    #+#                 */
/*   Updated: 2023/10/01 22:32:45 by daniel        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "main.h"
# define READ_END 0
# define WRITE_END 1

// exec.c
int			execute(t_cmd_table *cmd_table, t_env_list *env_list);

// pipe.c
int			execute_single_cmd(t_cmd_table *cmd_table);
int			execute_pipeline(t_cmd_table *cmd_table, int cmd_count, t_env_list *envl);
int			execute_main(t_cmd_table *cmd_table);

// redirect_multi.c
void		redirect(t_cmd_table *cmd_table, int fd[2], int read, int index, int pipe_count);
void		redirect_in(t_redirect *redirects, int read);
void		redirect_out(t_redirect *redirects, int fd[2], bool last_cmd);

// redirect_single.c
void		redirect_single(t_cmd_table *cmd_table);
void		redirect_single_in(t_redirect *redirects);
void		redirect_single_out(t_redirect *redirects);

// builtins.c
bool		check_builtin(t_cmd_table *cmd_table);
void		execute_builtin(t_cmd_table *cmd_table);

// errors.c
void		redirect_error(char *filename);
void		execute_error(char *cmd);
void 		ft_free(char **ptr);

#endif