/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_error.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-kle <dvan-kle@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/11 16:43:25 by dvan-kle      #+#    #+#                 */
/*   Updated: 2023/10/11 17:48:45 by dvan-kle      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/main.h"

bool	only_spaces(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (!ft_isspace(input[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	bracket_error(char *input)
{
	int		i;
	int		count;
	char	bracket;

	i = 0;
	count = 0;
	while (input[i])
	{
		if (input[i] == '\"' || input[i] == '\'')
		{
			count++;
			bracket = input[i];
			i++;
			while (input[i] && input[i] != bracket)
				i++;
			if (input[i] && input[i++] == bracket)
				count++;
		}
		else
			i++;
	}
	if (count % 2 != 0)
		return (ft_putstr_fd("minishell: unclosed brackets\n", STDERR_FILENO),
			true);
	return (false);
}

bool	parse_error_print(int x, char *input)
{
	if (x == 1)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		ft_putstr_fd(input, 2);
		ft_putstr_fd("'\n", 2);
	}
	else if (x == 2)
		ft_putstr_fd(
			"minishell: syntax error near unexpected token `newline'\n", 2);
	else if (x == 3)
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
	return (true);
}

bool	parse_error_check(t_token *t_list, char *input)
{
	t_token	*tmp;

	tmp = t_list;
	if (bracket_error(input) || only_spaces(input))
		return (true);
	while (tmp->type != END_OF_CMD_TOKEN)
	{
		if (ft_isredirect(tmp->type) && (tmp->next->type == PIPE_TOKEN
				|| ft_isredirect(tmp->next->type)))
			return (parse_error_print(1, tmp->next->value));
		if (ft_isredirect(tmp->type) && (tmp->next->type == END_OF_CMD_TOKEN))
			return (parse_error_print(2, NULL));
		if (tmp->type == PIPE_TOKEN && (tmp->next->type == END_OF_CMD_TOKEN
				|| !ft_strncmp(tmp->next->value, "$", 2)))
			return (parse_error_print(3, NULL));
		tmp = tmp->next;
	}
	return (false);
}

int	set_exit_and_free(t_token *token_list)
{
	int	exit_status;

	exit_status = 258;
	free_token_list(token_list);
	return (exit_status);
}
