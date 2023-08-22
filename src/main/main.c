/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/22 15:27:13 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/08/22 18:33:35 by tde-brui      ########   odam.nl         */
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
	return (line);
}

void	ft_leaks(void)
{
	system("leaks a.out");
}

int	check_builtin(char *input, t_cmd_table *cmd_table)
{
	char	**input_split;

	input_split = ft_split(input, ' ');
	if (!ft_strncmp(input, "exit", 4))
		exit(0);
	if (!ft_strncmp(input, "env", 3))
		env(cmd_table->env_list);
	if (!ft_strncmp(input, "export", 6))
		export(cmd_table->env_list, input_split[1]);
	if (!ft_strncmp(input, "unset", 5))
		unset(cmd_table->env_list, input_split[1]);
	if (!ft_strncmp(input, "cd", 2))
		cd(input_split[1]);
	if (ft_strncmp(input, "pwd", 3))
		pwd();
	free(input_split);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_cmd_table	*cmd_table;
	t_token		*token_list;
	char		*input;

	cmd_table = malloc(sizeof(t_cmd_table));
	cmd_table->env_list = make_env_list(envp);
	while (1)
	{
		input = get_line();
		if (check_builtin(input, cmd_table))
			break ;
		token_list = lexer(input);
		cmd_table = make_cmd_table(token_list);
		free_list(token_list);
	}
}
