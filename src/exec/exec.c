/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   folders.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-kle <dvan-kle@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/29 15:18:40 by dvan-kle      #+#    #+#                 */
/*   Updated: 2023/09/14 14:04:27 by dvan-kle      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../../libft/libft.h"
#include "../../incl/exec.h"
#include "../../incl/main.h"

bool	check_builtin(t_cmd_table *cmd_table, t_env_list *env_list)
{
	int	cmd_len;

	cmd_len = ft_strlen(cmd_table->args[0]);
	if (!ft_strncmp(cmd_table->args[0], "exit", cmd_len + 1))
		return (ft_exit(cmd_table), true);
	if (!ft_strncmp(cmd_table->args[0], "env", cmd_len))
		return (env(cmd_table->env_list), true);
	if (!ft_strncmp(cmd_table->args[0], "export", cmd_len))
		return (export(env_list, cmd_table->args[1]), true);
	if (!ft_strncmp(cmd_table->args[0], "unset", cmd_len))
		return (unset(env_list, cmd_table->args[1]), true);
	if (!ft_strncmp(cmd_table->args[0], "cd", cmd_len))
		return (cd(cmd_table->args[1]), true);
	if (!ft_strncmp(cmd_table->args[0], "pwd", cmd_len))
		return (printf("%s\n", getcwd(NULL, 0)), true);
	if (!ft_strncmp(cmd_table->args[0], "clear", cmd_len))
		return (printf("\033[2J\033[1;1H"), true);
	return (false);
}

static char	*check_access(char **folders, char *cmd)
{
	char	*check_access;
	char	*command_fold;
	int		i;

	i = 0;
	command_fold = ft_strjoin("/", cmd);
	if (!folders)
		return (cmd);
	while (folders[i])
	{
		check_access = ft_strjoin(folders[i], command_fold);
		if (access(check_access, X_OK | F_OK) == 0)
			return (check_access);
		i++;
	}
	return (cmd);
}

static char	*get_path(t_env_list *env_list, char *cmd)
{
	char	*path;
	char	**folders;

	path = NULL;
	while (env_list != NULL)
	{
		if (ft_strncmp(env_list->key, "PATH", 5) == 0)
			path = env_list->value;
		env_list = env_list->next;
	}
	folders = ft_split(path, ':');
	path = check_access(folders, cmd);
	free(folders);
	return (path);
}

int	execute(t_cmd_table *cmd_table, t_env_list *env_list)
{
	char	*path;

	path = get_path(env_list, cmd_table->args[0]);
	if (execve(path, cmd_table->args, NULL) == -1)
		return (execute_error(cmd_table->args[0]), EXIT_FAILURE);
	free(path);
	return (EXIT_SUCCESS);
}
