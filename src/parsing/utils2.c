/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils2.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/13 14:53:20 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/10/09 21:32:36 by tijmendebru   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/main.h"

t_token	check_new_cmd(t_token *token)
{
	if (token->new_cmd == true)
	{
		token->type = CMD_TOKEN;
		token->new_cmd = false;
	}
	else
		token->type = ARGUMENT_TOKEN;
	return (*token);
}

char	*minishell_strjoin(char const *str1, char const *str2)
{
	char	*ptr;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = ft_strlen(str1) + ft_strlen(str2) + 1;
	if (!str1)
		return ((char *)str1);
	if (!str2)
		str2 = ft_strdup("");
	ptr = ft_malloc((sizeof(char) * k));
	while (str1[i])
	{
		ptr[i] = str1[i];
		i++;
	}
	while (str2[j])
	{
		ptr[i + j] = str2[j];
		j++;
	}
	free((char *)str1);
	free((char *)str2);
	ptr[i + j] = '\0';
	return (ptr);
}

void	free_args(t_cmd_table *cmd_table)
{
	int	i;

	i = 0;
	while (cmd_table->args[i])
	{
		free(cmd_table->args[i]);
		i++;
	}
	free(cmd_table->args);
}

void	free_redirects(t_cmd_table	*cmd_table)
{
	int	i;

	i = 0;
	while (cmd_table->redirects[i].type != END_OF_CMD_TOKEN)
	{
		free(cmd_table->redirects[i].file);
		i++;
	}
	free(cmd_table->redirects);
}
