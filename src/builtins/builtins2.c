/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins2.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/19 16:07:42 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/10/06 18:00:25 by dvan-kle      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../../incl/env.h"
#include "../../libft/libft.h"

void	env(t_env_list *env_list)
{
	t_env_list	*lst_head;

	lst_head = env_list;
	while (lst_head)
	{
		printf("%s=%s\n", lst_head->key, lst_head->value);
		lst_head = lst_head->next;
	}
}

void	export(t_env_list *env_list, char **input)
{
	t_env_list	*curr;
	int			i;

	i = 1;
	curr = env_list;
	if (!input)
	{
		while (curr)
		{
			printf("declare -x %s=\"%s\"\n", curr->key, curr->value);
			curr = curr->next;
		}
		return ;
	}
	while (input[i])
	{
		env_add_back(input[i], &env_list);
		i++;
	}
}

void	unset(t_env_list *env_list, char *input)
{
	t_env_list	*lst_head;
	t_env_list	*lst_prev;

	lst_head = env_list;
	lst_prev = NULL;
	while (lst_head)
	{
		if (!ft_strncmp(lst_head->key, input, ft_strlen(lst_head->key)))
		{
			if (lst_prev)
				lst_prev->next = lst_head->next;
			else
				lst_head = lst_head->next;
			free(lst_head->key);
			free(lst_head->value);
			free(lst_head);
			return ;
		}
		lst_prev = lst_head;
		lst_head = lst_head->next;
	}
}
