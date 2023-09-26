/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipes.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-kle <dvan-kle@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/19 16:26:24 by dvan-kle      #+#    #+#                 */
/*   Updated: 2023/09/26 14:48:11 by daniel        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPES_H
# define PIPES_H

# define WRITE_END 1
# define READ_END 0

int	execute_pipeline(t_cmd_table *cmd_table, int cmd_count, t_env_list *envl);
bool	check_builtin(t_cmd_table *cmd_table);
void	execute_builtin(t_cmd_table *cmd_table);
bool	check_builtin2(t_cmd_table *cmd_table);
int     execute_single_cmd(t_cmd_table *cmd_table);
int     execute_main(t_cmd_table *cmd_table);

#endif