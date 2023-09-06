/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/30 11:01:16 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/08/30 18:24:46 by tde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"
#include "stdio.h"
#include "../../incl/tokenizer.h"
#include "../../incl/parser.h"

void	print_redirects(t_redirect *redir_arr)
{
	int	i;

	i = 0;
	while (redir_arr[i].type != 7)
	{
		printf("Type: %d, File: %s\n", redir_arr[i].type, redir_arr[i].file);
		i++;
	}
}