/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_table.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/30 14:36:33 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/09/27 15:53:29 by tde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/parser.h"

void	fill_cmd(t_token *token, t_cmd_table *new_cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (token->type != END_OF_CMD_TOKEN && token->type != PIPE_TOKEN)
	{
		if (ft_isredirect(token->type))
		{
			new_cmd->redirects[j].type = token->type;
			new_cmd->redirects[j].file = ft_strdup(token->next->value);
			j++;
			token = token->next;
		}
		else
		{
			new_cmd->args[i] = ft_strdup(token->value);
			i++;
		}
		if (token->type == END_OF_CMD_TOKEN)
			break ;
		token = token->next;
	}
	new_cmd->redirects[j].type = END_OF_CMD_TOKEN;
	new_cmd->args[i] = NULL;
}

t_cmd_table	*new_cmd(t_token *lst)
{
	t_cmd_table	*new_cmd;

	new_cmd = ft_malloc(sizeof(t_cmd_table));
	if (allocate_cmd_table(new_cmd, lst) == 1)
		exit(1);
	fill_cmd(lst, new_cmd);
	new_cmd->next = NULL;
	return (new_cmd);
}

t_cmd_table	*cmd_add_back(t_cmd_table *cmd_table, t_token *to_be_added)
{
	t_cmd_table	*lst;

	lst = cmd_table;
	if (!lst)
	{
		lst = new_cmd(to_be_added);
		return (lst);
	}
	while (lst->next != NULL)
		lst = lst->next;
	lst->next = new_cmd(to_be_added);
	return (cmd_table);
}

void	print_cmd_table(t_cmd_table *cmd_table)
{
	int			i;
	t_cmd_table	*tmp;

	tmp = cmd_table;
	while (tmp)
	{
		i = 0;
		printf("command : \n");
		while (tmp->args[i] != NULL)
		{
			printf("%s\n", tmp->args[i]);
			i++;
		}
		tmp = tmp->next;
	}
}

void	free_cmd_table(t_cmd_table *cmd_table)
{
	t_cmd_table	*tmp;
	t_cmd_table	*next;

	tmp = cmd_table;
	while (tmp != NULL)
	{
		free_args(tmp);
		free_redirects(tmp);
		if (tmp->next == NULL)
		{
			free(tmp);
			return ;
		}
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
}
