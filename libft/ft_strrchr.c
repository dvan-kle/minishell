/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrchr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 11:01:42 by tde-brui      #+#    #+#                 */
/*   Updated: 2022/10/21 15:14:59 by tde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int a)
{
	int				i;
	char			*ptr;

	i = 0;
	ptr = (char *)str;
	while (str[i])
	{
		i++;
	}
	while (i > -1)
	{
		if (str[i] == (char)a)
		{
			return (&ptr[i]);
		}
		i--;
	}
	return (NULL);
}
