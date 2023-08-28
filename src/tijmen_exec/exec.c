/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tijmendebruine <tijmendebruine@student.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/27 22:12:51 by tijmendebru   #+#    #+#                 */
/*   Updated: 2023/08/28 14:20:47 by tde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "../../incl/parser.h"
#include "../../incl/tokenizer.h"
#include "../../incl/main.h"

static char	**get_folders(void);

// int	execute_sgl_cmd(t_cmd_table *cmd_table)
// {
// 	char	*check_access;
// 	char	*command_fold;
// 	int		i;
// 	char	**folders;

// 	if (check_builtin(cmd_table) == true)
// 		return (0);
// 	folders = get_folders();
// 	command_fold = ft_strjoin("/", cmd_table->args[0]);
// 	i = 0;
// 	while (folders[i])
// 	{
// 		check_access = ft_strjoin(folders[i], command_fold);
// 		if (access(check_access, X_OK) == 0)
// 			execve(check_access, cmd_table->args, NULL);
// 		i++;
// 	}
// 	printf("not found\n");
// 	return (-1);
// }

// void	execute_mltpl_cmd(t_cmd_table *cmd_table)
// {
// 	t_cmd_table	*curr_table;
// 	int			status;
// 	int			fd[2];
// 	pid_t		pid;
// 	int			i;
// 	int			read;

// 	curr_table = cmd_table;
// 	i = 0;
// 	while (i < cmd_table->cmd_count)
// 	{
// 		pipe(fd);
// 		fork();
// 		if (pid == 0)
// 			execute_sgl_cmd(curr_table);
// 		waitpid(pid, &status, 0);
// 		i++;
// 		cmd_table = cmd_table->next;
// 	}
// }

// void	execute(t_cmd_table *cmd_table)
// {
// 	if (cmd_table->cmd_count == 1)
// 		execute_sgl_cmd(cmd_table);
// 	else
// 		printf("execute multiple commands\n");
// }

// int	main(int argc, char **argv, char **envp)
// {
// 	t_env_list	*env_list;
// 	t_token		*token_list;
// 	t_cmd_table	*cmd_table;

// 	env_list = make_env_list(envp);
// 	token_list = lexer("ls -la");
// 	cmd_table = make_cmd_table(token_list, env_list);
// 	execute(cmd_table);
// }