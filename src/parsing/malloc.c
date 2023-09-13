/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   malloc.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 14:07:07 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/09/12 14:07:24 by tde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		exit(1);
	return (ptr);
}
