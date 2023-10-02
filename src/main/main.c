/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/22 15:27:13 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/10/02 15:23:16 by tde-brui      ########   odam.nl         */
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
	if (!line)
	{
		write(STDERR_FILENO, "exit\n", 5);
		exit(0);
	}
	if (line[0] == '\0')
		return (NULL);
	add_history(line);
	return (line);
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
			if (input[i] && input[i] == bracket)
			{
				i++;
				count++;
			}
		}
		else
			i++;
	}
	if (count % 2 != 0)
	{
		printf("minishell: unclosed brackets\n");
		return (true);
	}
	return (false);
}

bool	parse_error_check(t_token *t_list, char *input)
{
	t_token	*tmp;

	tmp = t_list;
	if (bracket_error(input))
		return (true);
	while (tmp->type != END_OF_CMD_TOKEN)
	{
		if (ft_isredirect(tmp->type) && (tmp->next->type == PIPE_TOKEN
				|| ft_isredirect(tmp->next->type)))
		{
			printf("minishell: syntax error near unexpected token `%s'\n",
				tmp->next->value);
			return (true);
		}
		if (ft_isredirect(tmp->type) && (tmp->next->type == END_OF_CMD_TOKEN))
		{
			printf("minishell: syntax error near unexpected token `newline'\n");
			return (true);
		}
		if (tmp->type == PIPE_TOKEN && (tmp->next->type == END_OF_CMD_TOKEN
				|| !ft_strncmp(tmp->next->value, "$", 2)))
		{
			printf("minishell: syntax error near unexpected token `|'\n");
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
	int			exit_status;

	(void)argc;
	(void)argv;
	env_lst = make_env_list(envp);
	exit_status = 0;
	//atexit(ft_leaks);
	while (1)
	{
		init_signals();
		input = get_line();
		if (!input)
			continue ;
		token_list = lexer(input, env_lst, exit_status);
		if (parse_error_check(token_list, input))
		{
			exit_status = 258;
			free_token_list(token_list);
			continue ;
		}
		cmd_table = make_cmd_table(token_list, env_lst);
		free_token_list(token_list);
		exit_status = execute_main(cmd_table);
		free_cmd_table(cmd_table);
	}
	free_env_list(env_lst);
}
