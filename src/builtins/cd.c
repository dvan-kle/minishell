/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-kle <dvan-kle@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/06 16:07:50 by dvan-kle      #+#    #+#                 */
/*   Updated: 2023/10/09 21:30:32 by tijmendebru   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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

int	cd(const char *dir, t_cmd_table *cmd_table)
{
	t_env_list	*env_list;
	char		*path;

	env_list = cmd_table->env_list;
	path = NULL;
    if (!dir)
	{
		while (env_list != NULL)
		{
		if (ft_strncmp(env_list->key, "HOME", 5) == 0)
			path = ft_strdup(env_list->value);
		env_list = env_list->next;
		}
		if (!path)
			return (printf("minishell: cd: HOME not set\n"), EXIT_FAILURE);
	}
	else
		path = ft_strdup(dir);
	if (chdir(path) == -1)
		return (EXIT_FAILURE);
	set_new_pwd(cmd_table->env_list);
	free(path);
	return (0);
}
