/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_list_fncs.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/17 16:28:30 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/08/30 10:51:16 by tde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/tokenizer.h"

t_token	*new_token(t_token old_token)
{
	t_token	*n_token;

	n_token = malloc(sizeof(t_token));
	if (!n_token)
		exit(1);
	n_token->value = old_token.value;
	n_token->type = old_token.type;
	n_token->brackets = NULL;
	n_token->new_cmd = NULL;
	n_token->next = NULL;
	return (n_token);
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
	while (lst)
	{
		printf("Type: %d, Value: %s\n", lst->type, lst->value);
		lst = lst->next;
	}
}

void	free_token_list(t_token *token_list)
{
	t_token	*lst;
	t_token	*tmp;

	lst = token_list;
	while (lst)
	{
		tmp = lst->next;
		free(lst->value);
		free(lst);
		lst = tmp;
	}
}
