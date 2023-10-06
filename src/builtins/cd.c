/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-kle <dvan-kle@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/06 16:07:50 by dvan-kle      #+#    #+#                 */
/*   Updated: 2023/10/06 16:14:49 by dvan-kle      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "../../incl/main.h"

void	set_new_pwd(t_env_list *env_list)
{
	char	*old_pwd;

	old_pwd = replace_pwd(env_list);
	replace_old_pwd(env_list, old_pwd);
}

char	*replace_pwd(t_env_list *env_list)
{
	char	*pwd;
	char	*old_pwd;

	pwd = getcwd(NULL, 0);
	while (env_list != NULL)
	{
		if (ft_strncmp(env_list->key, "PWD", 5) == 0)
		{
			old_pwd = ft_strdup(env_list->value);
			free(env_list->value);
			env_list->value = ft_strdup(pwd);
			free(pwd);
		}
		env_list = env_list->next;
	}
	return (old_pwd);
}

void	replace_old_pwd(t_env_list *env_list, char *old_pwd)
{
	while (env_list != NULL)
	{
		if (ft_strncmp(env_list->key, "OLDPWD", 5) == 0)
		{
			free(env_list->value);
			env_list->value = ft_strdup(old_pwd);
			free(old_pwd);
		}
		env_list = env_list->next;
	}
}

int	cd(const char *path, t_cmd_table *cmd_table)
{
	if (chdir(path) == -1)
	{
		perror("cd");
		return (-1);
	}
	set_new_pwd(cmd_table->env_list);
	return (0);
}
