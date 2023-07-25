/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list_len.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/15 15:50:55 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/03/15 15:52:59 by tde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	list_len(t_list **stack)
{
	t_list	*head;
	int		i;

	head = (*stack);
	i = 0;
	while (head->next != NULL)
	{
		head = head->next;
		i++;
	}
	return (i);
}
