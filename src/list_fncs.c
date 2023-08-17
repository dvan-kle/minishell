/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list_fncs.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/17 16:28:30 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/08/17 17:39:25 by tde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/tokenizer.h"

t_token	*new_token(t_token token_to_be_added)
{
	t_token	*new_token;
	int		i;

	i = 0;
	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	while (token_to_be_added.value[i])
	{
		new_token->value[i] = token_to_be_added.value[i];
		i++;
	}
	new_token->value[i] = '\0';
	new_token->type = token_to_be_added.type;
	new_token->brackets = NULL;
	new_token->new_cmd = NULL;
	new_token->next = NULL;
	return (new_token);
}

t_token	*list_add_back(t_token *curr_list, t_token token_to_be_added)
{
	t_token	*lst;
	t_token	*curr;

	lst = curr_list;
	curr = curr_list;
	if (!lst)
	{
		lst = new_token(token_to_be_added);
		return (lst);
	}
	while (curr->next != NULL)
		curr = curr->next;
	curr->next = new_token(token_to_be_added);
	return (lst);
}

void	print_list(t_token *token_list)
{
	t_token	*lst;

	lst = token_list;
	while (lst->next != NULL)
	{
		ft_printf("Type: %d, Value: %s\n", lst->type, lst->value);
		lst = lst->next;
	}
}

void	free_list(t_token *token_list)
{
	t_token	*lst;
	t_token	*tmp;

	lst = token_list;
	while (lst != NULL)
	{
		tmp = lst->next;
		free(lst);
		lst = tmp;
	}
}
