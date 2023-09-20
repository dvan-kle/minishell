/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins2.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/19 16:07:42 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/09/20 15:23:49 by dvan-kle      ########   odam.nl         */
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
		dprintf(STDOUT_FILENO, "%s=%s\n", lst_head->key, lst_head->value);
		lst_head = lst_head->next;
	}
}

void	export(t_env_list *env_list, char *input)
{
	env_add_back(input, &env_list);
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

// int	main(int argc, char **argv, char **envp)
// {
// 	t_env_list	*env_list;

// 	env_list = make_env_list(envp);
// 	export(env_list, "TEST=TEST");
// 	export(env_list, "TEST2=TEST2");
// 	unset(env_list, "TEST");
// 	env(env_list);
// }
