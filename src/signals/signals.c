/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-kle <dvan-kle@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/02 18:01:23 by dvan-kle      #+#    #+#                 */
/*   Updated: 2023/08/02 18:16:07 by dvan-kle      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <sys/signal.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>

void	sig_handler(int signum)
{
	printf("\nminishell >");
}

int	main(void)
{
	while (1)
	{
		signal(SIGINT, sig_handler);
		sleep(1);
	}
	return (0);
}