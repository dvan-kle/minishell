/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/17 17:43:42 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/10/09 21:32:32 by tijmendebru   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/main.h"

void	init_token(t_token *token, t_env_list *env_lst)
{
	token->env_lst = env_lst;
	token->type = ARGUMENT_TOKEN;
	token->brackets = false;
	token->new_cmd = true;
	token->next = NULL;
	token->value = NULL;
	token->expand = false;
}

int	malloc_count(char *str, int i, char c)
{
	int	count;

	count = 0;
	while (str[i] && str[i] != c && !ft_isredirect(str[i]))
	{
		count++;
		i++;
	}
	return (count);
}

int	redir_count(t_token *lst)
{
	int		count;
	t_token	*curr;

	count = 0;
	curr = lst;
	while (curr->type != END_OF_CMD_TOKEN && curr->type != PIPE_TOKEN)
	{
		if (ft_isredirect(curr->type))
			count++;
		curr = curr->next;
	}
	return (count);
}

int	allocate_cmd_table(t_cmd_table *cmd_table, t_token *lst)
{
	cmd_table->args = ft_malloc(sizeof(char *) * (arg_token_count(lst) + 1));
	cmd_table->redirects = ft_malloc(sizeof(t_redirect)
			*(redir_count(lst) + 1));
	cmd_table = cmd_table->next;
	return (0);
}

int	arg_token_count(t_token *to_be_added)
{
	int		count;
	t_token	*curr;

	count = 0;
	curr = to_be_added;
	while (curr)
	{
		if (curr->type == ARGUMENT_TOKEN || curr->type == CMD_TOKEN)
			count++;
		curr = curr->next;
	}
	return (count);
}
