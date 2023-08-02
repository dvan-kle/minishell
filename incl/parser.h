/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/02 15:36:29 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/08/02 17:40:13 by tde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../libft/libft.h"

typedef enum nodetype
{
	CMD_NODE,
	ARG_NODE,
	PIPE_NODE,
	INPUT_REDIR_NODE,
	OUTPUT_REDIR_NODE,
	APPEND_REDIR_NODE,
	HEREDOC_REDIR_NODE
}t_nodetype;

typedef struct AST_NODE
{
	t_nodetype	node_type;
	char		*value;
	t_AST_NODE	*left_node;
	t_AST_NODE	*right_node;
}t_AST_NODE;

#endif