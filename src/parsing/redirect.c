/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/30 11:01:16 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/08/30 18:24:46 by tde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"
#include "stdio.h"
#include "../../incl/tokenizer.h"
#include "../../incl/parser.h"

void	print_redirects(t_redirect *redir_arr)
{
	int	i;

	i = 0;
	while (redir_arr[i].type != 7)
	{
		printf("Type: %d, File: %s\n", redir_arr[i].type, redir_arr[i].file);
		i++;
	}
}

bool	ft_isredirect(t_tokentype type)
{
	if (type == INPUT_REDIRECT_TOKEN || type == OUTPUT_REDIRECT_TOKEN
		|| type == APPEND_TOKEN || type == READ_INPUT_TOKEN)
		return (true);
	return (false);
}

bool	ft_isredir(char c)
{
	if (c == '<' || c == '>')
		return (true);
	return (false);
}

int	redir_count(t_token *lst)
{
	int		count;
	t_token	*curr;

	count = 0;
	curr = lst;
	while (curr->type != END_OF_CMD_TOKEN && curr->type != PIPE_TOKEN)
	{
		if (ft_isredirect(curr->type) && curr->next->type == ARGUMENT_TOKEN)
			count++;
		curr = curr->next;
	}
	return (count);
}
