/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_digits.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihuang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 19:52:23 by ihuang            #+#    #+#             */
/*   Updated: 2018/10/15 19:53:54 by ihuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_digits(int n)
{
	unsigned int	isneg;
	size_t			digits;

	isneg = 0;
	digits = 1;
	if (n == -2147483648)
		return (11);
	if (n < 0)
		isneg = 1;
	while (n / 10)
	{
		digits++;
		n /= 10;
	}
	return (isneg + digits);
}
