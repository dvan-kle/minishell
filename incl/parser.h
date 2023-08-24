/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/18 14:56:53 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/08/24 17:22:22 by tde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "env.h"

typedef struct s_cmd_table	t_cmd_table;

typedef struct s_cmd_table{
	char			**args;
	unsigned int	cmd_count;
	t_env_list		*env_list;
	t_cmd_table		*next;
}t_cmd_table;

#endif