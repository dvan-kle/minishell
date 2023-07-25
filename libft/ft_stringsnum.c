/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_stringsnum.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tijmendebruine <tijmendebruine@student.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/21 11:44:49 by tijmendebru   #+#    #+#                 */
/*   Updated: 2023/03/15 15:55:27 by tde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_stringsnum(char const *str1, char c)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = ft_strlen(str1);
	k = 0;
	if (ft_strncmp(str1, "", 1) == 0)
		return (0);
	while (str1[i])
	{
		while ((str1[i] == c) && str1[i] != '\0')
			i++;
		while (str1[i] != c && str1[i] != '\0')
			i++;
		k++;
	}
	if (str1[j - 1] == c && str1[j] == '\0')
		k -= 1;
	return (k);
}
