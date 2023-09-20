/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/18 15:05:38 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/09/20 15:50:26 by tde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/parser.h"
#include "../../incl/tokenizer.h"

bool	parse_error_check(t_token *t_list)
{
	t_token	*tmp;

	tmp = t_list;
	while (tmp->type != END_OF_CMD_TOKEN)
	{
		if (ft_isredirect(tmp->type) && (tmp->next->type == PIPE_TOKEN
				|| ft_isredirect(tmp->next->type)))
		{
			printf("minishell: syntax error near unexpected token`%s'\n", tmp->next->value);
			return (true);
		}
		if (ft_isredirect(tmp->type) && tmp->next->type == END_OF_CMD_TOKEN)
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
			return (true);
		}
		if (tmp->type == PIPE_TOKEN && tmp->next->type == END_OF_CMD_TOKEN)
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
			return (true);
		}
		tmp = tmp->next;
	}
	return (false);
}

t_cmd_table	*make_cmd_table(t_token	*token_list, t_env_list *env_list)
{
	t_cmd_table	*cmd_table;
	t_token		*curr_token;
	int			cmd_count;
	bool		error;


	cmd_table = NULL;
	curr_token = token_list;
	cmd_count = 0;
	error = parse_error_check(token_list);
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
	cmd_table->error = error;
	cmd_table->env_list = env_list;
	cmd_table->cmd_count = cmd_count + 1;
	return (cmd_table);
}
