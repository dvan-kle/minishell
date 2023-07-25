/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_put_addr.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/25 13:49:40 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/02/21 12:36:14 by tijmendebru   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_addr_len(unsigned long ptr)
{
	int	i;

	i = 0;
	if (ptr == 0)
		return (1);
	while (ptr > 0)
	{
		ptr = ptr / 16;
		i++;
	}
	return (i);
}

static char	*ft_lowhex_todec(unsigned long n)
{
	unsigned long	i;
	char			*ptr;
	int				temp;

	i = ft_addr_len(n);
	ptr = malloc((sizeof(char) * i) + 1);
	if (!ptr)
		return (NULL);
	ptr[i] = '\0';
	while (n > 0)
	{
		temp = n % 16;
		if (temp > 9)
			ptr[i - 1] = temp + 55 + 32;
		else
			ptr[i - 1] = temp + 48;
		i--;
		n = n / 16;
	}
	return (ptr);
}

int	ft_put_addr(void *ptr)
{
	int				length;
	unsigned long	i;
	char			*p;

	i = (unsigned long)ptr;
	p = ft_lowhex_todec(i);
	length = 0;
	length += printf_putstr("0x");
	if (!ptr)
		length += printf_putchar('0');
	else
	{
		printf_putstr(p);
		length += ft_addr_len(i);
	}
	free(p);
	return (length);
}
