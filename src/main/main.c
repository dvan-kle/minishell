/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/22 15:27:13 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/09/06 14:09:02 by dvan-kle      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/main.h"
#include <readline/readline.h>
#include <readline/history.h>

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

bool	check_builtin(t_cmd_table *cmd_table)
{
	int	cmd_len;

	cmd_len = ft_strlen(cmd_table->args[0]);
	if (!ft_strncmp(cmd_table->args[0], "exit", cmd_len))
		exit(1);
	if (!ft_strncmp(cmd_table->args[0], "env", cmd_len))
	{
		env(cmd_table->env_list);
		return (true);
	}
	if (!ft_strncmp(cmd_table->args[0], "export", cmd_len))
	{
		export(cmd_table->env_list, cmd_table->args[1]);
		return (true);
	}
	if (!ft_strncmp(cmd_table->args[0], "unset", cmd_len))
	{
		unset(cmd_table->env_list, cmd_table->args[1]);
		return (true);
	}
	if (!ft_strncmp(cmd_table->args[0], "cd", cmd_len))
	{
		cd(cmd_table->args[1]);
		return (true);
	}
	if (!ft_strncmp(cmd_table->args[0], "pwd", cmd_len))
	{
		printf("%s", getcwd(NULL, 0));
		return (true);
	}
	if (!ft_strncmp(cmd_table->args[0], "clear", cmd_len))
	{
		printf("\033[2J\033[1;1H");
		return (true);
	}
	return (false);
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

	argc = 0;
	argv = NULL;
	cmd_table = malloc(sizeof(t_cmd_table));
	cmd_table->env_list = make_env_list(envp);
	while (1)
	{
		input = get_line();
		if (!input)
			continue ;
		token_list = lexer(input);
		cmd_table = make_cmd_table(token_list, cmd_table->env_list);
		check_builtin(cmd_table);
		//free_token_list(token_list);
		//free_cmd_table(cmd_table);
		execute_main(cmd_table);
	}
	free_env_list(cmd_table->env_list);
}
