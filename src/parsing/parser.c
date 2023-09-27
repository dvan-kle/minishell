/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/18 15:05:38 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/09/27 13:52:09 by tde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/parser.h"
#include "../../incl/tokenizer.h"

t_cmd_table	*make_cmd_table(t_token	*token_list, t_env_list *env_list)
{
	t_cmd_table	*cmd_table;
	t_token		*curr_token;
	int			cmd_count;

	cmd_table = NULL;
	curr_token = token_list;
	cmd_count = 0;
	while (curr_token->type != END_OF_CMD_TOKEN)
	{
		cmd_table = cmd_add_back(cmd_table, curr_token);
		while (curr_token->type != 4 && curr_token->type != 7)
			curr_token = curr_token->next;
		if (curr_token->type == END_OF_CMD_TOKEN)
			break ;
		if (curr_token->type == PIPE_TOKEN)
			cmd_count++;
		curr_token = curr_token->next;
	}
	cmd_table->env_list = env_list;
	cmd_table->cmd_count = cmd_count + 1;
	return (cmd_table);
}
