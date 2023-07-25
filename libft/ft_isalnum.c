/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isalnum.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 11:00:48 by tde-brui      #+#    #+#                 */
/*   Updated: 2022/10/21 15:13:33 by tde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int a)
{
	if ((ft_isalpha(a) != 0) || (ft_isdigit(a) != 0))
	{
		return (1);
	}
	else
	{
		return (0);
	}
}
