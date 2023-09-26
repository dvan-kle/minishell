/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-kle <dvan-kle@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/29 15:18:40 by dvan-kle      #+#    #+#                 */
/*   Updated: 2023/09/26 12:17:41 by daniel        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../../libft/libft.h"
#include "../../incl/exec.h"
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

	path = get_path(env_list, cmd_table->args[0]);
	if (execve(path, cmd_table->args, NULL) == -1)
	{
		execute_error(cmd_table->args[0]);
		free(path);
		return (EXIT_FAILURE);
	}
	free(path);
	return (EXIT_SUCCESS);
}
