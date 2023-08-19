/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins2.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/19 16:07:42 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/08/19 17:51:10 by tde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../../libft/libft.h"

void	env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
}

char	**export(char **envp, char *input)
{
	int		i;
	int		env_count;
	char	**new_env;

	env_count = 0;
	while (envp[env_count])
		env_count++;
	new_env = malloc(sizeof(char *) * (env_count + 2));
	if (!new_env)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		if (i == (env_count - 2))
			new_env[i] = ft_strdup(input);
		else
			new_env[i] = ft_strdup(envp[i]);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

char	**unset(char **envp, char *argv)
{
	int		i;
	int		j;
	int		env_count;
	char	**new_env;

	i = 0;
	env_count = 0;
	while (envp[env_count])
		env_count++;
	new_env = malloc(sizeof(char *) * env_count);
	if (!new_env)
		return (NULL);
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] == argv[j] && envp[i][j] != '=')
			j++;
		if (envp[i][j] != '=')
			new_env[i] = ft_strdup(envp[i]);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

int	main(int argc, char **argv, char **envp)
{
	argc = 1;
	envp = export(envp, argv[1]);
	env(envp);
	envp = unset(envp, "lol");
	env(envp);
}
