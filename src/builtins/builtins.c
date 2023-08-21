/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-kle <dvan-kle@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/26 13:31:44 by dvan-kle      #+#    #+#                 */
/*   Updated: 2023/08/21 17:21:19 by tde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int	cd(const char *path)
{
	if (chdir(path) == -1)
	{
		perror("cd");
		return (-1);
	}
	return (0);
}

int main(void)
{
	char *pwd = getcwd(NULL, 0);
	printf("%s\n", pwd);
	cd("..");
	pwd = getcwd(NULL, 0);
	printf("%s\n", pwd);
	cd("../tijmen_test");
	pwd = getcwd(NULL, 0);
	printf("%s\n", pwd);
}
