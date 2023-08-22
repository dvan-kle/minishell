/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/18 15:05:38 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/08/22 17:56:11 by tde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/parser.h"
#include "../../incl/tokenizer.h"

int	arg_token_count(t_token *to_be_added)
{
	int	count;

	count = 0;
	while (to_be_added->type != PIPE_TOKEN && to_be_added->type != END_OF_CMD_TOKEN)
	{
		if (to_be_added->type == 1)
			count++;
		to_be_added = to_be_added->next;
	}
	return (count);
}

t_cmd_table	*new_cmd(t_token *to_be_added)
{
	t_cmd_table	*new_cmd;
	int			i;
	int			value_len;

	new_cmd = malloc(sizeof(t_cmd_table));
	if (!new_cmd)
		return (NULL);
	new_cmd->args = malloc(sizeof(char *) * (arg_token_count(to_be_added) + 1));
	if (!new_cmd->args)
		return (free(new_cmd), NULL);
	i = 0;
	while (to_be_added->type != PIPE_TOKEN && to_be_added->type != END_OF_CMD_TOKEN)
	{
		if (to_be_added->type == CMD_TOKEN)
			new_cmd->cmd = to_be_added->value;
		else
		{
			value_len = ft_strlen(to_be_added->value);
			new_cmd->args[i] = malloc(value_len + 1);
			if (!new_cmd->args[i])
				return (free(new_cmd), free(new_cmd->args), NULL);
			ft_strlcpy(new_cmd->args[i], to_be_added->value, value_len + 1);
			i++;
		}
		to_be_added = to_be_added->next;
	}
	new_cmd->args[i] = NULL;
	new_cmd->next = NULL;
	return (new_cmd);
}

t_cmd_table	*cmd_add_back(t_cmd_table *cmd_table, t_token *to_be_added)
{
	t_cmd_table	*lst;
	t_cmd_table	*curr;

	lst = cmd_table;
	if (!lst)
	{
		lst = new_cmd(to_be_added);
		return (lst);
	}
	curr = cmd_table;
	while (curr->next != NULL)
		curr = curr->next;
	curr->next = new_cmd(to_be_added);
	return (lst);
}

void	print_cmd_table(t_cmd_table *cmd_table)
{
	int	i;

	while (cmd_table != NULL)
	{
		i = 0;
		printf("COMMAND : %s\n", cmd_table->cmd);
		printf("ARGS : \n");
		while (cmd_table->args[i] != NULL)
		{
			printf("%s\n", cmd_table->args[i]);
			i++;
		}
		cmd_table = cmd_table->next;
	}
}

t_cmd_table	*make_cmd_table(t_token	*token_list)
{
	t_cmd_table	*cmd_table;
	t_token		*curr_token;

	cmd_table = NULL;
	curr_token = token_list;
	while (curr_token->type != END_OF_CMD_TOKEN)
	{
		cmd_table = cmd_add_back(cmd_table, curr_token);
		while (curr_token->type != 4 && curr_token->type != 7)
			curr_token = curr_token->next;
		if (curr_token->type == END_OF_CMD_TOKEN)
			break ;
		curr_token = curr_token->next;
	}
	print_cmd_table(cmd_table);
	return (cmd_table);
}
