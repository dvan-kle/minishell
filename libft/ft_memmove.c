/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 11:01:22 by tde-brui      #+#    #+#                 */
/*   Updated: 2022/10/21 15:17:06 by tde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t num)
{
	unsigned long	j;
	char			*ptrsrc;
	char			*ptrdest;

	j = num;
	ptrsrc = (char *)src;
	ptrdest = (char *)dest;
	if (src == 0 && dest == 0)
		return (NULL);
	if (dest > src)
	{
		while (j-- > 0)
			ptrdest[j] = ptrsrc[j];
	}
	else
	{
		j = 0;
		while (j < num)
		{
			ptrdest[j] = ptrsrc[j];
			j++;
		}
	}
	return (dest);
}
