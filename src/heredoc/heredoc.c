/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tijmendebruine <tijmendebruine@student.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/09 19:57:11 by tijmendebru   #+#    #+#                 */
/*   Updated: 2023/10/10 14:01:34 by tijmendebru   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/main.h"

void	heredoc(char *eof, t_cmd_table *cmd_table, int pipe[2])
{
    int     i;
    char    *line;

    line = NULL;
    i = 0;
    while (1)
    {
        line = readline("> ");
        if (!line)
            exit(130);
        if (!ft_strncmp(line, eof, ft_strlen(eof) + 1))
            break ;
        write(pipe[WRITE_END], line, ft_strlen(line));
        write(pipe[WRITE_END], "\n", 1);
        free(line);
    }
    free(line);
}