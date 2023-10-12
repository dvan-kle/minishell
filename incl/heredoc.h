/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-kle <dvan-kle@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/10 12:08:52 by dvan-kle      #+#    #+#                 */
/*   Updated: 2023/10/12 17:30:21 by dvan-kle      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

# include "main.h"

int		check_heredoc(t_cmd_table *cmd_table);
void	exec_heredoc(char *delim, int fd[2]);
int		heredoc(t_cmd_table *cmd_table);
bool	infile_check(t_redirect *head);

#endif