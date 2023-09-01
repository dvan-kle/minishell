/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_malloc.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/30 19:17:55 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/08/31 14:00:09 by tde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/parser.h"

int	malloc_count(char *str, int i, char c)
{
	int	count;

	count = 0;
	while (str[i] && !ft_isspace(str[i]) && str[i] != c)
	{
		count++;
		i++;
	}
	return (count);
}

int	redir_count(t_token *lst)
{
	int	count;

	count = 0;
	while (lst->type != END_OF_CMD_TOKEN && lst->type != PIPE_TOKEN)
	{
		if (ft_isredirect(lst->type) && lst->next->type == ARGUMENT_TOKEN)
			count++;
		lst = lst->next;
	}
	return (count);
}

int	allocate_cmd_table(t_cmd_table *cmd_table, t_token *lst)
{
	cmd_table->args = malloc(sizeof(char *) * (arg_token_count(lst) + 1));
	if (!cmd_table->args)
		return (1);
	cmd_table->redirects = malloc(sizeof(t_redirect) * (redir_count(lst) + 1));
	if (!cmd_table->redirects)
		return (1);
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
