/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-kle <dvan-kle@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/26 13:31:44 by dvan-kle      #+#    #+#                 */
/*   Updated: 2023/10/06 16:07:33 by dvan-kle      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "../../incl/main.h"

void	pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	printf("%s\n", pwd);
	free(pwd);
}

void	echo(t_cmd_table	*cmd_table)
{
	int			i;
	t_cmd_table	*curr;

	i = 1;
	curr = cmd_table;
	if (curr->args[i] && !ft_strncmp(curr->args[i], "-n", 3))
		i++;
	while (curr->args[i])
	{
		if (!curr->args[i + 1])
			printf("%s", curr->args[i]);
		else
			printf("%s ", curr->args[i]);
		i++;
	}
	if (!curr->args[1] || ft_strncmp(curr->args[1], "-n", 3))
		printf("\n");
}
