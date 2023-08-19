/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 15:01:21 by tde-brui      #+#    #+#                 */
/*   Updated: 2022/10/21 15:13:46 by tde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *ptr, int value, size_t size)
{
	unsigned long	i;
	char			*ptr1;

	i = 0;
	ptr1 = (char *)ptr;
	while (i < size)
	{
		if (ptr1[i] == (char)value)
		{
			return (&ptr1[i]);
		}
		i++;
	}
	return (NULL);
}
