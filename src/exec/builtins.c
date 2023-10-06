/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-kle <dvan-kle@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/06 16:53:54 by dvan-kle      #+#    #+#                 */
/*   Updated: 2023/10/06 18:00:15 by dvan-kle      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../../libft/libft.h"
#include "../../incl/exec.h"
#include "../../incl/main.h"

bool	check_builtin(t_cmd_table *cmd_table)
{
	int	cmd_len;

	cmd_len = ft_strlen(cmd_table->args[0]) + 1;
	if (!ft_strncmp(cmd_table->args[0], "env", cmd_len))
		return (true);
	if (!ft_strncmp(cmd_table->args[0], "export", cmd_len))
		return (true);
	if (!ft_strncmp(cmd_table->args[0], "unset", cmd_len))
		return (true);
	if (!ft_strncmp(cmd_table->args[0], "clear", cmd_len))
		return (true);
	if (!ft_strncmp(cmd_table->args[0], "exit", cmd_len))
		return (true);
	if (!ft_strncmp(cmd_table->args[0], "cd", cmd_len))
		return (true);
	if (!ft_strncmp(cmd_table->args[0], "pwd", cmd_len))
		return (true);
	return (false);
}

void	execute_builtin(t_cmd_table *cmd_table)
{
	int	cmd_len;

	cmd_len = ft_strlen(cmd_table->args[0]) + 1;
	if (!ft_strncmp(cmd_table->args[0], "exit", cmd_len))
		ft_exit(cmd_table);
	if (!ft_strncmp(cmd_table->args[0], "cd", cmd_len))
		cd(cmd_table->args[1], cmd_table);
	if (!ft_strncmp(cmd_table->args[0], "pwd", cmd_len))
		pwd();
	if (!ft_strncmp(cmd_table->args[0], "export", cmd_len))
		export(cmd_table->env_list, cmd_table->args);
	if (!ft_strncmp(cmd_table->args[0], "unset", cmd_len))
		unset(cmd_table->env_list, cmd_table->args[1]);
	if (!ft_strncmp(cmd_table->args[0], "clear", cmd_len))
		printf("\033[2J\033[1;1H");
	if (!ft_strncmp(cmd_table->args[0], "env", cmd_len))
		env(cmd_table->env_list);
	if (cmd_table->cmd_count > 1)
		exit(EXIT_SUCCESS);
}
