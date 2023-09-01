/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipes.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-kle <dvan-kle@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/19 16:26:24 by dvan-kle      #+#    #+#                 */
/*   Updated: 2023/09/01 16:49:16 by dvan-kle      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPES_H
# define PIPES_H

# define WRITE_END 1
# define READ_END 0

void	execute_pipeline(t_cmd_table *cmd_table, int pipe_count);
void	execute_single_cmd(t_cmd_table *cmd_table);
void	execute_main(t_cmd_table *cmd_table);

#endif