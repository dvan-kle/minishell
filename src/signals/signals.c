/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-kle <dvan-kle@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/02 18:01:23 by dvan-kle      #+#    #+#                 */
/*   Updated: 2023/09/23 17:14:10 by daniel        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <sys/signal.h>
#include <stdio.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdlib.h>

void	sigquit_handler(int sigquit)
{
	(void)sigquit;
	printf("Quit (core dumped)\n");
	exit(1);
}

void	sigint_handler(int sigint)
{
	(void)sigint;
	printf("\n");
	rl_on_new_line();
	//rl_replace_line("", 0);
	rl_redisplay();
}

void	init_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
}

void	ignore_signals(void)
{
	signal(SIGINT, SIG_IGN);
}
