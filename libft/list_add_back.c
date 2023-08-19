/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list_add_back.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/15 15:54:06 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/07/25 14:41:51 by tde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	list_add_back(t_list **stack_a, int value)
{
	t_list	*head;

	head = (*stack_a);
	if ((*stack_a) == NULL)
		(*stack_a) = list_new(value);
	else
	{
		while (head->next != NULL)
			head = head->next;
		head->next = list_new(value);
	}
}
