/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_get_int.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/25 14:33:53 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/02/21 12:37:21 by tijmendebru   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_get_int(int n)
{
	char	*ptr;

	ptr = ft_itoa(n);
	printf_putstr(ptr);
	free(ptr);
	return (ft_len(n));
}
