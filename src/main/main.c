/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/22 15:27:13 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/09/25 21:32:56 by tijmendebru   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/main.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

char	*get_line(void)
{
	static char	*line;

	if (line)
		free(line);
	line = readline("minishell$ ");
	if (line[0] == '\0')
		return (NULL);
	add_history(line);
	return (line);
}

bool	parse_error_check(t_token *t_list)
{
	t_token	*tmp;

	tmp = t_list;
	while (tmp->type != END_OF_CMD_TOKEN)
	{
		if (ft_isredirect(tmp->type) && (tmp->next->type == PIPE_TOKEN
				|| ft_isredirect(tmp->next->type)))
		{
			printf("minishell: syntax error near unexpected token `%s'\n", tmp->next->value);
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

void	ft_leaks(void)
{
	system("leaks minishell");
}

int	main(int argc, char **argv, char **envp)
{
	t_cmd_table	*cmd_table;
	t_token		*token_list;
	t_env_list	*env_lst;
	char		*input;

	(void)argc;
	(void)argv;
	env_lst = make_env_list(envp);
	while (1)
	{
		init_signals();
		input = get_line();
		if (!input)
			continue ;
		token_list = lexer(input, env_lst);
		if (parse_error_check(token_list))
		{
			free_token_list(token_list);
			continue ;
		}
		cmd_table = make_cmd_table(token_list, env_lst);
		free_token_list(token_list);
		execute_main(cmd_table);
		free_cmd_table(cmd_table);
	}
	free_env_list(env_lst);
}
