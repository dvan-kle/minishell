/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list_new.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/15 15:52:42 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/03/15 15:52:57 by tde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*list_new(int value)
{
	t_list	*new_node;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
		exit(1);
	new_node->data = value;
	new_node->next = NULL;
	return (new_node);
}
