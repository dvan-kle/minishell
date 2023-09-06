/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 11:01:35 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/09/06 12:56:20 by dvan-kle      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = -1;
	j = ft_strlen(src);
	if (size <= 0 || !dest)
		return (0);
	if (size == 0)
		return (ft_strlen(src));
	if (size > ft_strlen(src))
	{
		while (src[++i])
			dest[i] = src[i];
	}
	else
	{
		while (src[++i] && i < size - 1)
			dest[i] = src[i];
	}
	dest[i] = '\0';
	return (j);
}
