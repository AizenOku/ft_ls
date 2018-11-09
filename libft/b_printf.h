/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_printf.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihuang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 17:41:39 by ihuang            #+#    #+#             */
/*   Updated: 2018/10/03 11:49:14 by ihuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef B_PRINTF_H
# define B_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

int		ft_write(char c);
int		ft_putstr(char *s);
char	*ft_strchr(const char *s, int c);
char	*convert(unsigned long num, int base);
int		print_memory(va_list list);
int		handle2(const char c, va_list list);
int		handle(const char c, va_list list);
int		parse_format(const char *fmt, va_list list);
int		b_printf(const char *restrict format, ...);

#endif
