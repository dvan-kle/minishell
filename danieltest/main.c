/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-kle <dvan-kle@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/25 14:59:32 by dvan-kle      #+#    #+#                 */
/*   Updated: 2023/07/29 13:53:15 by dvan-kle      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// int main(int ac, char **av)
// {
// 	int i = 0;
// 	char *env = getenv("?");
// 	// while (env[i])
// 	// {
// 	// 	printf("%s\n", env[i]);
// 	// 	i++;
// 	// }
// 	printf("%s\n", env);
// 	return (0);
// }

// int main(void)
// {
// 	char *str = ttyname(0);
// 	printf("%s\n", str);
// 	int slot = ttyslot();
// 	printf("%d\n", slot);
// 	execve("/bin/ls", "-la", NULL);
// }

// int main() {
//     char *argv[] = {"/bin/cat", "-e", NULL};  // Example: running 'ls -l'
//     char *envp[] = {NULL};  // Use the current environment

//     // Replace the current process image with 'ls -l'
//     if (execve("/bin/cat", argv, envp) == -1) {
//         perror("execve");
//         return (1);
//     }

//     // This code will only be executed if execve() fails (which is unlikely)
//     printf("This won't be printed.\n");

//     return (0);
// }

// void clearTerminal() {
//    
	// ANSI escape sequence to clear the screen and set cursor position to the top-left corner
//     ft_printf("\033[2J\033[H");
// }

// int main() {
//     // Call the function to clear the terminal
//     clearTerminal();

//     // Display a message after clearing
//     // ft_printf("Terminal Cleared!\n");

//     return (0);
// }

// void env(char **envp)
// {
// 	int i = 0;
// 	while (envp[i])
// 	{
// 		printf("%s\n", envp[i]);
// 		i++;
// 	}
// }

// int	main(void)
// {
// 	char pwd[100];

// 	getcwd(pwd, 100);
// 	printf("%s\n", pwd);

// 	char *user;
// 	user = getenv("USER");
// 	printf("%s\n", user);
// }
