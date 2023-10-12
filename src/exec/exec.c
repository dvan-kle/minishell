/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-kle <dvan-kle@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/29 15:18:40 by dvan-kle      #+#    #+#                 */
/*   Updated: 2023/10/12 15:35:45 by dvan-kle      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/main.h"

static char	*check_access(char **folders, char *cmd)
{
	char	*check_access;
	char	*command_fold;
	int		i;

	i = 0;
	if (!folders)
		return (cmd);
	command_fold = ft_strjoin("/", cmd);
	while (folders[i])
	{
		check_access = ft_strjoin(folders[i], command_fold);
		if (access(check_access, X_OK | F_OK) == 0)
			return (free(command_fold), check_access);
		i++;
		free(check_access);
	}
	free(command_fold);
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
	ft_free(folders);
	return (path);
}

int	execute(t_cmd_table *cmd_table, t_env_list *env_list)
{
	char	*path;
	char	**envp;

	if (cmd_table->args[0] == NULL)
		return (EXIT_SUCCESS);
	path = get_path(env_list, cmd_table->args[0]);
	envp = env_list_to_char(env_list);
	if (execve(path, cmd_table->args, envp) == -1)
	{
		execute_error(cmd_table->args[0]);
		free(path);
		free(envp);
		return (EXIT_FAILURE);
	}
	free(path);
	free(envp);
	return (EXIT_SUCCESS);
}
