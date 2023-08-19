/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/08 16:29:22 by tde-brui      #+#    #+#                 */
/*   Updated: 2022/10/21 15:16:20 by tde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str1, const char *str2, size_t size)
{
	size_t		i;
	size_t		j;
	size_t		checkpoint;
	const char	*ptr;

	i = 0;
	if (*str2 == '\0')
		return ((char *)&str1[i]);
	while (str1[i] && i < size)
	{
		ptr = &str1[i];
		j = 0;
		checkpoint = i;
		while (str1[i] == str2[j] && i < size && str1[i] != '\0')
		{
			j++;
			i++;
		}
		i = checkpoint;
		if (str2[j] == '\0')
			return ((char *)ptr);
		else
			i++;
	}
	return (NULL);
}
