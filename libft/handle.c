/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihuang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 22:12:52 by ihuang            #+#    #+#             */
/*   Updated: 2018/09/30 23:15:02 by ihuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "b_printf.h"

int		handle(const char c, va_list list)
{
	char			*s;
	char			ch;

	if (c == 'c' || c == '%')
	{
		if (c == '%')
			ch = '%';
		else
			ch = va_arg(list, int);
		write(1, &ch, 1);
		return (1);
	}
	else if (c == 's')
	{
		if ((s = va_arg(list, char*)) != NULL)
			return (ft_putstr(s));
		else
			return (ft_putstr("(null)"));
	}
	return (handle2(c, list));
}

int		handle2(const char c, va_list list)
{
	int				i;
	unsigned int	u;

	if (c == 'd' || c == 'i')
	{
		i = va_arg(list, int);
		if (i < 0)
		{
			write(1, "-", 1);
			return (1 + ft_putstr(convert((unsigned int)-i, 10)));
		}
		else
			return (ft_putstr(convert((unsigned int)i, 10)));
	}
	else if (c == 'u' || c == 'x' || c == 'o')
	{
		u = va_arg(list, unsigned int);
		if (c == 'u')
			return (ft_putstr(convert(u, 10)));
		else if (c == 'o')
			return (ft_putstr(convert(u, 8)));
		else if (c == 'x')
			return (ft_putstr(convert(u, 16)));
	}
	return (print_memory(list));
}

int		print_memory(va_list list)
{
	void			*ptr;

	write(1, "0x", 2);
	ptr = va_arg(list, void*);
	if (ptr == NULL)
		return (2 + ft_putstr("0"));
	return (2 + ft_putstr(convert((unsigned long)ptr, 16)));
}
