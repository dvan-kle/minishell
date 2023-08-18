/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/18 15:05:38 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/08/18 18:02:47 by tde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/parser.h"
#include "../incl/tokenizer.h"

int	arg_token_count(t_token *to_be_added)
{
	if (!to_be_added)
		return (0);
	if (!to_be_added->next)
		return (1);
	while ()
}

t_cmd_table	*new_cmd(t_token *to_be_added)
{
	t_cmd_table	*new_cmd;
	int			i;
	int			value_len;

	new_cmd = malloc(sizeof(t_cmd_table));
	if (!new_cmd)
		return (NULL);
	i = 0;
	while (to_be_added->type != 4 && to_be_added->type != 7)
	{
		if (to_be_added->type == 0)
			new_cmd->cmd = to_be_added->value;
		else
		{
			value_len = ft_strlen(to_be_added->value);
			new_cmd->args[i] = malloc(value_len + 1);
			if (!new_cmd->args[i])
				return (NULL);
			ft_strlcpy(new_cmd->args[i], to_be_added->value, value_len);
			i++;
		}
		to_be_added = to_be_added->next;
		//new_cmd->args[i] = NULL;
	}
	return (new_cmd);
}

t_cmd_table	*make_cmd_table(t_token	*token_list)
{
	t_cmd_table	*cmd_table;

	cmd_table = NULL;
	cmd_table = new_cmd(token_list);
	return (cmd_table);
}

int main()
{
	t_token		*token_list;
	t_cmd_table	*cmd_table;
	int			i;

	i = 0;
	token_list = lexer("ls -l | wc -l | grep make");
	cmd_table = make_cmd_table(token_list);
	printf("command :%s\n", cmd_table->cmd);
	while (cmd_table->args[i])
	{
		printf("args: \n");
		printf("%s\n", cmd_table->args[i]);
		i++;
	}
}
