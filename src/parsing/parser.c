/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/18 15:05:38 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/10/12 16:13:45 by tde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/main.h"

int	count_commands(t_token *token_list)
{
	int		count;
	t_token	*curr_token;

	count = 0;
	curr_token = token_list;
	while (curr_token->type != END_OF_CMD_TOKEN)
	{
		if (curr_token->type == PIPE_TOKEN)
			count++;
		curr_token = curr_token->next;
	}
	return (count + 1);
}

t_cmd_table	*make_cmd_table(t_token	*token_list, t_env_list *env_list)
{
	t_cmd_table	*cmd_table;
	t_token		*curr_token;
	int			cmd_count;

	cmd_table = NULL;
	curr_token = token_list;
	cmd_count = count_commands(token_list);
	while (curr_token->type != END_OF_CMD_TOKEN)
	{
		cmd_table = cmd_add_back(cmd_table, curr_token, cmd_count, env_list);
		while (curr_token->type != 4 && curr_token->type != 7)
			curr_token = curr_token->next;
		if (curr_token->type == END_OF_CMD_TOKEN)
			break ;
		curr_token = curr_token->next;
	}
	return (cmd_table);
}
