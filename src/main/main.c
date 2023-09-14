/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/22 15:27:13 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/09/14 15:06:58 by tde-brui      ########   odam.nl         */
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
	system("leaks a.out");
}

int	main(int argc, char **argv, char **envp)
{
	t_cmd_table	*cmd_table;
	t_token		*token_list;
	char		*input;

	(void)argc;
	(void)argv;
	cmd_table = malloc(sizeof(t_cmd_table));
	cmd_table->env_list = make_env_list(envp);
	while (1)
	{
		init_signals();
		input = get_line();
		if (!input)
			continue ;
		token_list = lexer(input, cmd_table->env_list);
		cmd_table = make_cmd_table(token_list, cmd_table->env_list);
		execute_main(cmd_table);
		//free_token_list(token_list);
		// free_cmd_table(cmd_table);
	}
	free_env_list(cmd_table->env_list);
}
