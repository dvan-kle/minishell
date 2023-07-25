/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcpy.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 11:01:18 by tde-brui      #+#    #+#                 */
/*   Updated: 2022/10/21 15:13:49 by tde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t size)
{
	unsigned long	i;
	char			*ptr;
	char			*ptr1;

	i = 0;
	ptr = (char *)src;
	ptr1 = (char *)dest;
	if (ptr == 0 && ptr1 == 0)
		return (0);
	while (i < size)
	{
		ptr1[i] = ptr[i];
		i++;
	}
	return (dest);
}
