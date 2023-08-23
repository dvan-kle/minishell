/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-kle <dvan-kle@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/26 15:18:01 by dvan-kle      #+#    #+#                 */
/*   Updated: 2023/08/22 16:50:29 by tde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>


// int main(void)
// {
// 	pid_t	pid;

// 	pid = fork();
// 	if (pid == -1)
// 		return (perror("fork"), 1);
// 	if (pid == 0)
// 	{
// 		printf("I am the child process\n");
// 		printf("PID: %d\n", pid);
// 	}
// 	if (pid > 0)
// 	{
// 		printf("I am the parent process\n");
// 		printf("PID: %d\n", pid);
// 	}
// }