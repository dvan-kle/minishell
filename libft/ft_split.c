/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/14 11:46:05 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/02/21 12:40:45 by tijmendebru   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_free(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}

static size_t	split_len(char const *str1, char c, int i)
{
	int	k;

	k = 0;
	while (str1[i] != c && str1[i] != '\0')
	{
		i++;
		k++;
	}
	return (k);
}

char	**ft_split(char const *str1, char c)
{
	char				**ptr;
	unsigned int		i;
	int					j;

	i = 0;
	j = 0;
	ptr = (char **)malloc((ft_stringsnum(str1, c) + 1) * sizeof(char *));
	if (!ptr)
		return (NULL);
	while (j < ft_stringsnum(str1, c))
	{
		while (str1[i] == c && str1[i] != '\0')
			i++;
		ptr[j] = ft_substr(str1, i, split_len(str1, c, i));
		if (!ptr[j])
		{
			ft_free(ptr);
			return (NULL);
		}
		while (str1[i] != c && str1[i] != '\0')
			i++;
		j++;
	}
	ptr[j] = 0;
	return (ptr);
}
