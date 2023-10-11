/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_list_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-kle <dvan-kle@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/11 16:07:36 by dvan-kle      #+#    #+#                 */
/*   Updated: 2023/10/11 16:07:53 by dvan-kle      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/main.h"

t_env_list	*make_env_list(char **envp)
{
	t_env_list	*new_env_list;
	int			i;

	i = 1;
	new_env_list = new_env(envp[0]);
	while (envp[i])
	{
		env_add_back(envp[i], &new_env_list);
		i++;
	}
	return (new_env_list);
}

char	**env_list_to_char(t_env_list *env_list)
{
	t_env_list	*curr;
	char		**envp;
	char		*key;
	int			i;

	i = 0;
	curr = env_list;
	envp = ft_malloc(sizeof(char *) * (ft_env_size(env_list) + 1));
	while (curr)
	{
		key = ft_strjoin(curr->key, "=");
		envp[i] = ft_strjoin(key, curr->value);
		curr = curr->next;
		i++;
		free(key);
	}
	envp[i] = NULL;
	return (envp);
}

int	ft_env_size(t_env_list *env_list)
{
	t_env_list	*curr;
	int			i;

	i = 0;
	curr = env_list;
	while (curr)
	{
		curr = curr->next;
		i++;
	}
	return (i);
}
