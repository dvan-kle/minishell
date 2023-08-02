/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/02 15:35:32 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/08/02 18:00:31 by tde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/parser.h"
#include <stdio.h>

t_AST_NODE	*new_ast_node(t_nodetype node_type, char *value)
{
	t_AST_NODE	*new_node;

	new_node = (t_AST_NODE *)malloc(sizeof(t_AST_NODE *));
	if (!new_node)
		return (NULL);
	new_node->node_type = node_type;
	new_node->value = value;
	new_node->left_node = NULL;
	new_node->right_node = NULL;
	return (new_node);
}
