/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-kle <dvan-kle@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/26 13:31:44 by dvan-kle      #+#    #+#                 */
/*   Updated: 2023/10/09 19:30:11 by tijmendebru   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "../../incl/main.h"

int	cd(const char *path)
{
	if (chdir(path) == -1)
	{
		perror("cd");
		return (-1);
	}
	return (0);
}

void	pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	printf("%s\n", pwd);
	free(pwd);
}

void	print_echo_args(t_cmd_table *cmd_table, int i, bool option)
{
	t_cmd_table *curr;

	curr = cmd_table;
	while (curr->args[i])
	{
		if (!curr->args[i + 1])
			printf("%s", curr->args[i]);
		else
			printf("%s ", curr->args[i]);
		i++;
	}
	if (!option)
		printf("\n");
}

void	echo(t_cmd_table	*cmd_table)
{
	int			i;
	int			j;
	t_cmd_table	*curr;
	bool		option;

	i = 1;
	curr = cmd_table;
	option = false;
	while (curr->args[i] && !ft_strncmp(curr->args[i], "-n", 2))
	{
		j = 2;
		while (curr->args[i][j] == 'n')
			j++;
		if (curr->args[i][j] == '\0')
			option = true;
		else
			break ;
		i++;
	}
	print_echo_args(cmd_table, i, option);
}
