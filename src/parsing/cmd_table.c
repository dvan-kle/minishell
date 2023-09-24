/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_table.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/30 14:36:33 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/09/24 15:26:38 by tijmendebru   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/parser.h"

t_cmd_table	*new_cmd(t_token *lst)
{
	t_cmd_table	*new_cmd;
	int			i;
	int			j;

	new_cmd = ft_malloc(sizeof(t_cmd_table));
	if (allocate_cmd_table(new_cmd, lst) == 1)
		exit(1);
	i = 0;
	j = 0;
	while (lst->type != END_OF_CMD_TOKEN && lst->type != PIPE_TOKEN)
	{
		if (ft_isredirect(lst->type))
		{
			new_cmd->redirects[j].type = lst->type;
			new_cmd->redirects[j].file = ft_strdup(lst->next->value);
			j++;
			lst = lst->next;
		}
		else
		{
			new_cmd->args[i] = ft_strdup(lst->value);
			if (!new_cmd->args[i])
				exit(1);
			i++;
		}
		if (lst->type == END_OF_CMD_TOKEN)
			break ;
		lst = lst->next;
	}
	new_cmd->redirects[j].type = END_OF_CMD_TOKEN;
	new_cmd->args[i] = NULL;
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
	int			i;
	t_cmd_table	*tmp;
	t_cmd_table *next;

	tmp = cmd_table;
	while (tmp != NULL)
	{
		i = 0;
		while (tmp->args[i])
		{
			free(tmp->args[i]);
			i++;
		}
		i = 0;
		while (tmp->redirects[i].type != END_OF_CMD_TOKEN)
		{
			free(tmp->redirects[i].file);
			i++;
		}
		free(tmp->args);
		free(tmp->redirects);
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
