/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/01 11:58:39 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/09/26 14:01:24 by daniel        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/parser.h"
#include <stdlib.h>
#include <limits.h>

long long	long_atoi(char *input)
{
	unsigned long long	result;
	unsigned long long	max;
	int					sign;

	result = 0;
	sign = 1;
	if (*input == '-')
	{
		sign = -1;
		input++;
	}
	else if (*input == '+')
		input++;
	while (*input >= '0' && *input <= '9')
	{
		result *= 10;
		result += *input - '0';
		input++;
	}
	max = __LONG_LONG_MAX__;
	if ((result > max && sign == 1) || ((result > max + 1) && sign == -1))
		return (-1);
	return (result * sign);
}

void	numeric_error_exit(char *str)
{
	printf("minishell: exit: %s: numeric argument required\n",
		str);
	exit(255);
}

void	error_check(char *str)
{
	int			i;

	i = 0;
	if ((str[0] == '+' || str[0] == '-') && str[1])
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			numeric_error_exit(str);
		i++;
	}
}

void	check_len(char *str)
{
	if (str[0] == '+' || str[0] == '-')
	{
		if (ft_strlen(str) > 20)
			numeric_error_exit(str);
	}
	else if (ft_strlen(str) > 19)
		numeric_error_exit(str);
}

void	ft_exit(t_cmd_table *cmd_table)
{
	ft_putstr_fd("exit\n", STDERR_FILENO);
	if (cmd_table->args[1] != NULL)
	{
		error_check(cmd_table->args[1]);
		check_len(cmd_table->args[1]);
		if (long_atoi(cmd_table->args[1]) == -1)
			numeric_error_exit(cmd_table->args[1]);
		if (cmd_table->args[2])
		{
			printf("minishell: exit: too many arguments\n");
			return ;
		}
		if (long_atoi(cmd_table->args[1]) != -1)
			exit(long_atoi(cmd_table->args[1]) % 256);
	}
	else
		exit(0);
}
