/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: daniel <daniel@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/09 21:15:22 by daniel        #+#    #+#                 */
/*   Updated: 2023/10/10 10:06:46 by daniel        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/main.h"

bool check_heredoc(t_cmd_table *cmd_table)
{
	t_redirect	*redirect;

	redirect = cmd_table->redirects;
	while(redirect != END_OF_CMD_TOKEN)
	{
		if (redirect->type == READ_INPUT_TOKEN)
		{
			dprintf(2, "heredoc\n");
			return (true);
		}	
		redirect++;
	}
	return (false);
}
