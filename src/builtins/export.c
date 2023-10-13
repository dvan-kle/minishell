/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: daniel <daniel@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/09 19:26:33 by daniel        #+#    #+#                 */
/*   Updated: 2023/10/11 19:19:11 by dvan-kle      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/main.h"

void	export(t_env_list *env_list, char **input)
{
	t_env_list	*curr;
	int			i;

	i = 1;
	curr = env_list;
	if (!input[1])
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

void	export_error(char *input)
{
	printf("minishell: export: `%s': not a valid identifier\n", input);
}

int	export_input_check(char *key, char *input)
{
	int	i;

	i = 1;
	if (!key[0])
		return (export_error(input), EXIT_FAILURE);
	if (ft_isdigit(key[0]) || (!ft_isalpha(key[0]) && key[0] != '_'))
		return (export_error(input), EXIT_FAILURE);
	while (key[i] && key[i] != '=')
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (export_error(input), EXIT_FAILURE);
		i++;
	}
	return (0);
}
