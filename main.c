/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihuang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 22:51:54 by ihuang            #+#    #+#             */
/*   Updated: 2018/11/09 08:47:05 by ihuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		main(int ac, char **av)
{
	t_params		*pp;
	t_ll			*file_ll;
	t_ll			*dir_ll;
	char			c;

	ac = 0;
	pp = initiate_params();
	file_ll = NULL;
	dir_ll = NULL;
	if ((c = get_params(av, &pp)) == 0)
	{
		av += pp->count + 1;
		get_list(av, &file_ll, &dir_ll, pp);
		print_all(file_ll, dir_ll, pp);
	}
	else
		print_illegal_option(c);
	free(pp);
	return (0);
}

void	print_illegal_option(char c)
{
	ft_putstr("ls: illegal option -- ");
	ft_putchar(c);
	ft_putendl("\nusage: ls [-larRt] [file ...]");
}

char	*make_path(char *big, char *small)
{
	char	*temp;
	char	*path;

	temp = ft_strjoin(big, "/");
	path = ft_strjoin(temp, small);
	free(temp);
	return (path);
}
