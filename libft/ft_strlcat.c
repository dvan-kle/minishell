/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcat.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 11:01:32 by tde-brui      #+#    #+#                 */
/*   Updated: 2022/10/21 15:16:30 by tde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	unsigned long	i;
	unsigned long	j;
	unsigned long	k;
	unsigned long	sum;

	i = ft_strlen(dest);
	j = ft_strlen(src);
	sum = i + j;
	k = 0;
	if (i >= size)
		return (j + size);
	while (i < size - 1 && src[k])
	{
		dest[i] = src[k];
		k++;
		i++;
	}
	if (i < size)
	{
		dest[i] = '\0';
	}
	return (sum);
}
