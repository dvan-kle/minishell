/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/23 14:45:36 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/02/21 12:33:31 by tijmendebru   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>

int	ft_format(va_list list, char format)
{
	int	length;

	length = 0;
	if (format == 'c')
		length += printf_putchar(va_arg(list, int));
	else if (format == 's')
		length += printf_putstr(va_arg(list, char *));
	else if (format == 'd' || format == 'i')
		length += ft_get_int(va_arg(list, int));
	else if (format == 'u')
		length += ft_unsigned_dec(va_arg(list, unsigned int));
	else if (format == '%')
		length += printf_putchar('%');
	else if (format == 'x')
		length += ft_lower_hexa(va_arg(list, unsigned int));
	else if (format == 'X')
		length += ft_upper_hexa(va_arg(list, unsigned int));
	else if (format == '\0')
		return (0);
	else if (format == 'p')
		length += ft_put_addr(va_arg(list, void *));
	else
		length++;
	return (length);
}

int	ft_printf(const char *str, ...)
{
	int		length;
	int		i;
	va_list	list;

	length = 0;
	i = 0;
	va_start(list, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			length += ft_format(list, str[i + 1]);
			i++;
		}
		else
			length += printf_putchar(str[i]);
		if (str[i] != '\0')
			i++;
	}
	va_end(list);
	return (length);
}
