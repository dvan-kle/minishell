/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   folders.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-kle <dvan-kle@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/29 15:18:40 by dvan-kle      #+#    #+#                 */
/*   Updated: 2023/09/07 14:56:37 by dvan-kle      ########   odam.nl         */
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
	if (!ft_strncmp(cmd_table->args[0], "exit", cmd_len))
		exit(1);
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
	while (folders[i])
	{
		check_access = ft_strjoin(folders[i], command_fold);
		// dprintf(2, "check_access: %s\n", check_access);
		if (access(check_access, X_OK) == 0)
		{
			// dprintf(2, "check_access: ok!\n");
			return (check_access);
		}
		i++;
	}
	return (cmd);
}

static char	*get_path(t_env_list *env_list, char *cmd)
{
	char	*path;
	char	**folders;

	while (env_list != NULL)
	{
		if (ft_strncmp(env_list->key, "PATH", 5) == 0)
		{
			// dprintf(2, "key: %s\n", env_list->key);
			path = env_list->value;
		}
		env_list = env_list->next;
	}
	// dprintf(2, "path: %s\n", path);
	folders = ft_split(path, ':');
	path = check_access(folders, cmd);
	return (path);
}

int	execute(t_cmd_table *cmd_table, t_env_list *env_list)
{
	char	*path;

	if (check_builtin(cmd_table, env_list))
		return (0);
	path = get_path(env_list, cmd_table->args[0]);
	if (access(path, X_OK) != 0)
	{
		perror("minishell");
		// printf("minishell: command not found: %s\n", args[0]);
		//return (0);
	}
	execve(path, cmd_table->args, NULL);
	return (0);
}
