/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-kle <dvan-kle@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/10 12:08:52 by dvan-kle      #+#    #+#                 */
/*   Updated: 2023/10/13 01:23:42 by daniel        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

# include "main.h"

int		check_heredoc(t_cmd_table *cmd_table);
void	exec_heredoc(char *delim, int fd[2], int count, t_env_list *env_lst);
int		heredoc(t_cmd_table *cmd_table);
bool	infile_check(t_redirect *head);
void	signal_heredoc(int sig);
char	*get_last_delim(t_cmd_table *cmd_table, int i);
char	*expand_heredoc(char *line, t_env_list *env_lst);
char	*heredoc_var(char *line, int i, t_env_list *env_lst);

#endif