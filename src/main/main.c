/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/22 15:27:13 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/09/26 15:10:45 by daniel        ########   odam.nl         */
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
	int 		exit_status;

	(void)argc;
	(void)argv;
	env_lst = make_env_list(envp);
	exit_status = 0;
	// atexit(ft_leaks);
	while (1)
	{
		init_signals();
		input = get_line();
		if (!input)
			continue ;
		token_list = lexer(input, env_lst);
		cmd_table = make_cmd_table(token_list, env_lst);
		free_token_list(token_list);
		if (cmd_table->error == 0)
			exit_status = execute_main(cmd_table);
		free_cmd_table(cmd_table);
	}
	free_env_list(cmd_table->env_list);
}
