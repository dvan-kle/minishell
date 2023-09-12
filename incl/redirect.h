/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-kle <dvan-kle@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/01 13:03:49 by dvan-kle      #+#    #+#                 */
/*   Updated: 2023/09/12 16:13:41 by dvan-kle      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECT_H
# define REDIRECT_H

# include <stdbool.h>

void	redirect(t_cmd_table *cmd_table, int fd[2], int read, int index, int pipe_count);
void	redirect_in(t_redirect *redirects, int read);
void	redirect_out(t_redirect *redirects, int fd[2], bool last_cmd);
void	redirect_single(t_cmd_table *cmdtable);
void	redirect_single_in(t_redirect *redirects);
void	redirect_single_out(t_redirect *redirects);

#endif