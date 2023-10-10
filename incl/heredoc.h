/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-kle <dvan-kle@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/10 12:08:52 by dvan-kle      #+#    #+#                 */
/*   Updated: 2023/10/10 13:40:15 by dvan-kle      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

# include "main.h"

bool	check_heredoc(t_cmd_table *cmd_table);
void	exec_heredoc(char *delim, int fd[2]);
int		heredoc(t_cmd_table *cmd_table);

#endif