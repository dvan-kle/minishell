/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-kle <dvan-kle@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/06 16:07:50 by dvan-kle      #+#    #+#                 */
/*   Updated: 2023/10/13 13:09:44 by dvan-kle      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/main.h"

void	set_new_pwd(t_env_list *env_list)
{
	char	*old_pwd;

	old_pwd = replace_pwd(env_list);
	if (old_pwd)
		replace_old_pwd(env_list, old_pwd);
}

char	*replace_pwd(t_env_list *env_list)
{
	char	*pwd;
	char	*old_pwd;

	pwd = getcwd(NULL, 0);
	old_pwd = NULL;
	while (env_list != NULL)
	{
		if (ft_strncmp(env_list->key, "PWD", 4) == 0)
		{
			old_pwd = ft_strdup(env_list->value);
			free(env_list->value);
			env_list->value = ft_strdup(pwd);
		}
		env_list = env_list->next;
	}
	free(pwd);
	return (old_pwd);
}

void	replace_old_pwd(t_env_list *env_list, char *old_pwd)
{
	while (env_list != NULL)
	{
		if (ft_strncmp(env_list->key, "OLDPWD", 7) == 0)
		{
			free(env_list->value);
			env_list->value = ft_strdup(old_pwd);
			free(old_pwd);
		}
		env_list = env_list->next;
	}
}

void	chdir_error(void)
{
	if (errno == EACCES)
		ft_putstr_fd("minishell: cd: permission denied\n", 2);
	else if (errno == ENOENT)
		ft_putstr_fd("minishell: cd: no such file or directory\n", 2);
	else if (errno == ENOTDIR)
		ft_putstr_fd("minishell: cd: not a directory\n", 2);
	else if (errno == ENAMETOOLONG)
		ft_putstr_fd("minishell: cd: filename too long\n", 2);
	else if (errno == ELOOP)
		ft_putstr_fd("minishell: cd: too many levels of symbolic links\n", 2);
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
			return (ft_putendl_fd("minishell: cd: HOME not set", 2),
				EXIT_FAILURE);
	}
	else
		path = ft_strdup(dir);
	if (chdir(path) == -1)
		return (free(path), chdir_error(), EXIT_FAILURE);
	set_new_pwd(cmd_table->env_list);
	free(path);
	return (0);
}
