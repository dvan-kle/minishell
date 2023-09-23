/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_list_fncs.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/21 16:41:49 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/09/23 17:33:21 by tijmendebru   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../../incl/env.h"
#include "../../libft/libft.h"
#include "../../incl/tokenizer.h"

t_env_list	*new_env(char *env)
{
	t_env_list	*nenv;

	nenv = ft_malloc(sizeof(t_env_list));
	nenv->key = ft_substr(env, 0, ft_strchr(env, '=') - env);
	nenv->value = ft_substr(env, ft_strchr(env, '=') - env + 1, ft_strlen(env));
	nenv->next = NULL;
	return (nenv);
}

void	env_add_back(char *env, t_env_list **env_list)
{
	t_env_list	*lst_head;

	lst_head = *env_list;
	while (lst_head->next)
		lst_head = lst_head->next;
	lst_head->next = new_env(env);
}

void	free_env_list(t_env_list *env_list)
{
	t_env_list	*curr;

	curr = env_list;
	while (curr)
	{
		free(curr->key);
		free(curr->value);
		free(curr);
		curr = curr->next;
	}
}

int	env_count(char	**envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

t_env_list	*make_env_list(char	**envp)
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
