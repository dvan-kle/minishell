/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/22 15:27:13 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/08/27 19:07:38 by tijmendebru   ########   odam.nl         */
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

void	ft_leaks(void)
{
	system("leaks a.out");
}

bool	check_builtin(char *input, t_cmd_table *cmd_table)
{
	char	**input_split;

	input_split = ft_split(input, ' ');
	if (!ft_strncmp(input, "exit", 4))
		exit(1);
	if (!ft_strncmp(input, "env", 3))
		env(cmd_table->env_list);
	if (!ft_strncmp(input, "export", 6))
		export(cmd_table->env_list, input_split[1]);
	if (!ft_strncmp(input, "unset", 5))
		unset(cmd_table->env_list, input_split[1]);
	if (!ft_strncmp(input, "cd", 2))
		cd(input_split[1]);
	if (!ft_strncmp(input, "pwd", 3))
		printf("%s", getcwd(NULL, 0));
	free(input_split);
	return (0);
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
		if (check_builtin(input, cmd_table))
			break ;
		token_list = lexer(input);
		cmd_table = make_cmd_table(token_list, cmd_table->env_list);
		free_token_list(token_list);
		free_cmd_table(cmd_table);
	}
	free_env_list(cmd_table->env_list);
}
