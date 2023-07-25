/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 16:23:42 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/02/21 11:37:49 by tijmendebru   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_start(char const *str, char const *set)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (set[j])
	{
		if (set[j] == str[i])
		{
			i++;
			j = 0;
		}
		else
			j++;
	}
	return (i);
}

static int	ft_end(char const *str, char const *set)
{
	int	i;
	int	j;
	int	k;

	i = ft_strlen(str) - 1;
	j = 0;
	k = 0;
	if (i < 0)
		return (0);
	while (set[j])
	{
		if (str[i] == set[j])
		{
			j = 0;
			k++;
			i--;
		}
		else
			j++;
	}
	return (k);
}

char	*ft_strtrim(char const *str, char const *set)
{
	int		start;
	int		end;
	char	*ptr;
	int		sum;

	start = ft_start(str, set);
	end = ft_end(str, set);
	sum = ft_strlen(str) - start - end;
	if (!str)
		return ((char *)str);
	if (!set)
		return (ft_strdup(str));
	ptr = ft_substr(str, start, sum);
	return (ptr);
}
