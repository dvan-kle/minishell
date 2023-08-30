/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/22 15:27:13 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/08/30 19:03:27 by tde-brui      ########   odam.nl         */
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
	if (!ft_strncmp(cmd_table->args[0], "exit", 4))
		exit(1);
	if (!ft_strncmp(cmd_table->args[0], "env", 3))
	{
		env(cmd_table->env_list);
		return (true);
	}
	if (!ft_strncmp(cmd_table->args[0], "export", 6))
	{
		export(cmd_table->env_list, cmd_table->args[1]);
		return (true);
	}
	if (!ft_strncmp(cmd_table->args[0], "unset", 5))
	{
		unset(cmd_table->env_list, cmd_table->args[1]);
		return (true);
	}
	if (!ft_strncmp(cmd_table->args[0], "cd", 2))
	{
		cd(cmd_table->args[1]);
		return (true);
	}
	if (!ft_strncmp(cmd_table->args[0], "pwd", 3))
	{
		printf("%s", getcwd(NULL, 0));
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
	}
	free_env_list(cmd_table->env_list);
}
