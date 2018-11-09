/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihuang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/04 09:38:57 by ihuang            #+#    #+#             */
/*   Updated: 2018/11/08 22:46:34 by ihuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_ll(t_ll *head, t_params *p)
{
	while (head)
	{
		ls(head->ent, p);
		head = head->next;
	}
}

t_ll	*print_dirll(t_ll *dir_ll, int multiple, t_params *p)
{
	t_ll	*temp;
	
	temp = NULL;
	temp = mkdir_cont(dir_ll->ent->name, p);
	if (p->rflag)
		lstrev(&temp);
	if (p->Rflag || multiple)
		printf("%s:\n", dir_ll->ent->name);
	if (p->lflag && temp)
		print_total(temp, p);
	print_ll(temp, p);
	return (temp);
}

void	print_all(t_ll *file_ll, t_ll *dir_ll, t_params *p)
{
	t_ll	*dir_ll_start;
	t_ll	*temp;
	int		multiple;

	dir_ll_start = dir_ll;
	print_ll(file_ll, p);
	temp = NULL;
	if (file_ll && dir_ll)
		write(1, "\n", 1);
	multiple = (file_ll || (dir_ll && dir_ll->next)) ? 1 : 0;
	while (dir_ll)
	{
		if (p->Rflag)
			print_recursively(dir_ll, p);
		else
			temp = print_dirll(dir_ll, multiple, p);
		if (dir_ll->next)
			write(1, "\n", 1);	
		dir_ll = dir_ll->next;
		free_ll(&temp);
	}
	free_ll(&file_ll);
	free_ll(&dir_ll_start);
}

/*
** make a func called print_all
** which will take in a file_ll, dir_ll, and print everything in order
*/

/*
** print_recursively
** 2. if dir, print out contents of dir
** 3. if content of dir is dir
*/

void	print_recursively(t_ll *list, t_params *p)
{
	t_ll	*temp;
	t_ll	*temp_start;
	char	*path;
	char	*ptr;
	
	temp = NULL;
	ptr = ft_strrchr(list->ent->name, '/');
	if (!p->aflag && ptr && *(ptr + 1) == '.')
		return ;
	else if (S_ISDIR(list->ent->mode))
	{
		temp = print_dirll(list, 1, p);
		temp_start = temp;
		if (temp)
			write(1, "\n", 1);
		while (temp)
		{
			if (S_ISDIR(temp->ent->mode))
			{
				ptr = ft_strrchr(temp->ent->name, '/');
				if (ptr && ft_strcmp(ptr + 1, ".") != 0 \
						&& ft_strcmp(ptr + 1, "..") != 0)
					print_recursively(temp, p);
			}
			temp = temp->next;
		}
		free_ll(&temp_start);
	}
}
