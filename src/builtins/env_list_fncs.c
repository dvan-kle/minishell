/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_list_fncs.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/21 16:41:49 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/10/11 16:08:33 by dvan-kle      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/main.h"

t_env_list	*new_env(char *env)
{
	t_env_list	*nenv;

	nenv = ft_malloc(sizeof(t_env_list));
	nenv->key = ft_substr(env, 0, ft_strchr(env, '=') - env);
	if (export_input_check(nenv->key, env) == EXIT_FAILURE)
	{
		free(nenv->key);
		free(nenv);
		return (NULL);
	}
	nenv->value = ft_substr(env, ft_strchr(env, '=') - env + 1, ft_strlen(env));
	nenv->next = NULL;
	return (nenv);
}

char	*assign_and_free(t_env_list *lst_head, t_env_list *tmp)
{
	char	*value;

	free(lst_head->value);
	value = tmp->value;
	free(tmp->key);
	free(tmp);
	return (value);
}

void	env_add_back(char *env, t_env_list **env_list)
{
	t_env_list	*lst_head;
	t_env_list	*prev;
	t_env_list	*tmp;

	lst_head = *env_list;
	tmp = new_env(env);
	if (!tmp)
		return ;
	if (!lst_head)
	{
		*env_list = tmp;
		return ;
	}
	while (lst_head)
	{
		if (!ft_strncmp(lst_head->key, tmp->key, ft_strlen(tmp->key) + 1))
		{
			lst_head->value = assign_and_free(lst_head, tmp);
			return ;
		}
		prev = lst_head;
		lst_head = lst_head->next;
	}
	prev->next = tmp;
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

int	env_count(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}
