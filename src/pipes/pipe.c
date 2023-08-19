/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
<<<<<<< HEAD:src/pipes/pipe.c
/*   pipe.c                                             :+:    :+:            */
=======
/*   ft_isspace.c                                       :+:    :+:            */
>>>>>>> master:src/builtins/ft_isspace.c
/*                                                     +:+                    */
/*   By: dvan-kle <dvan-kle@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
<<<<<<< HEAD:src/pipes/pipe.c
/*   Created: 2023/08/19 13:00:29 by dvan-kle      #+#    #+#                 */
/*   Updated: 2023/08/19 13:15:45 by dvan-kle      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int fd;

	fd = open("test.txt", O_RDWR);

	dup2(fd, STDIN_FILENO);


}
=======
/*   Created: 2023/08/02 13:02:05 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/08/02 13:03:00 by tde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int	ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == 13)
		return (1);
	return (0);
}
>>>>>>> master:src/builtins/ft_isspace.c
