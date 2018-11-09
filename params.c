/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihuang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 22:55:54 by ihuang            #+#    #+#             */
/*   Updated: 2018/11/04 01:23:16 by ihuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_params	*initiate_params(void)
{
	t_params		*p;

	p = (t_params*)malloc(sizeof(t_params));
	p->lflag = 0;
	p->aflag = 0;
	p->tflag = 0;
	p->rflag = 0;
	p->Rflag = 0;
	p->count = 0;
	return (p);
}

char		get_params(char **av, t_params **pp)
{
	int				j;
	int				i;

	i = 0;
	while (av[++i] && av[i][0] == '-')
	{
		if (av[i][1] == '-' || av[i][1] == '\0')
			return (av[i][1]);
		j = 0;
		while (av[i][++j])
		{
			if (ft_strchr("latrR", av[i][j]))
				add_param(av[i][j], *pp);
			else
				return (av[i][j]);
		}
		(*pp)->count++;
	}
	return (0);
}

void		add_param(char c, t_params *p)
{
	if (c == 'l')
		p->lflag = 1;
	else if (c == 'a')
		p->aflag = 1;
	else if (c == 't')
		p->tflag = 1;
	else if (c == 'r')
		p->rflag = 1;
	else if (c == 'R')
		p->Rflag = 1;
	else
		return ;
}
