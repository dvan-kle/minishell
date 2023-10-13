/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins2.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/19 16:07:42 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/10/13 12:33:18 by dvan-kle      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/main.h"

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

void	unset_env(t_env_list *env_list, char *input)
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

void	unset(t_env_list *env_list, char **input)
{
	int	i;

	i = 1;
	while (input[i])
	{
		unset_env(env_list, input[i]);
		i++;
	}
}
