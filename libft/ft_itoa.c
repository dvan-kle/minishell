/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/12 18:52:07 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/02/21 12:38:49 by tijmendebru   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_min_int(char *str)
{
	char	*lol;
	int		i;

	i = 0;
	lol = "-2147483648";
	while (lol[i])
	{
		str[i] = lol[i];
		i++;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char	*ptr;
	int		j;

	j = ft_len(n);
	ptr = (char *)malloc(ft_len(n) + 1);
	if (ptr == 0)
		return (0);
	ptr[j] = '\0';
	if (n < 0)
	{
		ptr[0] = '-';
		n *= -1;
	}
	while (n > 9)
	{
		ptr[j - 1] = (n % 10) + 48;
		j--;
		n = n / 10;
	}
	if (n > -1 && n < 10)
		ptr[j - 1] = n + 48;
	if (n == -2147483648)
		ptr = ft_min_int(ptr);
	return (ptr);
}
