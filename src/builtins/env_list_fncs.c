/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_list_fncs.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/21 16:41:49 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/09/25 21:16:14 by tijmendebru   ########   odam.nl         */
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
	t_env_list	*tmp;

	lst_head = *env_list;
	tmp = new_env(env);
	while (lst_head)
	{
		if (!ft_strncmp(lst_head->key, tmp->key, ft_strlen(tmp->key) + 1))
		{
			free(lst_head->value);
			lst_head->value = tmp->value;
			free(tmp->key);
			free(tmp);
			return ;
		}
		lst_head = lst_head->next;
	}
	if (!lst_head)
	{
		lst_head = *env_list;
		while (lst_head->next)
			lst_head = lst_head->next;
		lst_head->next = tmp;
		return ;
	}
	lst_head->next = tmp;
}

void	free_env_list(t_env_list *env_list)
{
	t_env_list	*curr;
	t_env_list	*temp;

	curr = env_list;
	while (curr)
	{
		temp = curr->next;
		free(curr->key);
		free(curr->value);
		free(curr);
		curr = temp;
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
