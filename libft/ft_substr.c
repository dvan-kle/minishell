/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 14:06:07 by tde-brui      #+#    #+#                 */
/*   Updated: 2022/10/21 17:54:44 by tde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *str, unsigned int start, size_t len)
{
	size_t				i;
	size_t				j;
	char				*ptr;

	i = 0;
	j = 0;
	if (!str)
		return ((char *)str);
	if ((size_t)start > ft_strlen(str))
		return (ft_strdup(""));
	if (len > ft_strlen(str))
		len = ft_strlen(str);
	ptr = malloc(((sizeof(char)) * len) + 1);
	if (!ptr)
		return (NULL);
	while (str[start + i] != '\0' && i < len && start <= ft_strlen(str))
	{
		ptr[j] = str[start + i];
		i++;
		j++;
	}
	ptr[j] = '\0';
	return (ptr);
}
