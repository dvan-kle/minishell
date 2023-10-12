/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-kle <dvan-kle@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/10 12:08:52 by dvan-kle      #+#    #+#                 */
/*   Updated: 2023/10/12 16:42:00 by tde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

# include "main.h"

int		check_heredoc(t_cmd_table *cmd_table);
void	exec_heredoc(char *delim, int fd[2], t_env_list *env_lst);
int		heredoc(t_cmd_table *cmd_table);
char	*ft_charjoin(char *str, char c);
char	*expand_heredoc(char *line, t_env_list *env_lst);
char	*heredoc_var(char *line, int i, t_env_list *env_lst);

#endif