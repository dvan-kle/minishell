/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/22 15:27:13 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/10/12 17:39:46 by tde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/main.h"

char	*get_line(void)
{
	static char	*line;

	if (line)
		free(line);
	line = readline("minishell$ ");
	if (!line)
	{
		write(STDERR_FILENO, "exit\n", 5);
		exit(130);
	}
	if (line[0] == '\0')
		return (NULL);
	add_history(line);
	return (line);
}

int	cmd_table_and_exec(t_token *token_list, t_env_list *env_list)
{
	t_cmd_table	*cmd_table;
	int			exit_status;

	cmd_table = make_cmd_table(token_list, env_list);
	free_token_list(token_list);
	exit_status = execute_main(cmd_table);
	free_cmd_table(cmd_table);
	return (exit_status);
}

int	main(int argc, char **argv, char **envp)
{
	t_token		*token_list;
	t_env_list	*env_lst;
	char		*input;
	int			exit_status;

	(void)argc;
	(void)argv;
	env_lst = make_env_list(envp);
	exit_status = 0;
	while (1)
	{
		init_signals();
		input = get_line();
		if (!input)
			continue ;
		token_list = lexer(input, env_lst, exit_status);
		if (parse_error_check(token_list, input))
		{
			exit_status = set_exit_and_free(token_list);
			continue ;
		}
		exit_status = cmd_table_and_exec(token_list, env_lst);
		break ;
	}
	free_env_list(env_lst);
}
