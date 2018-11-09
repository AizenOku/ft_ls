/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihuang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/03 21:00:08 by ihuang            #+#    #+#             */
/*   Updated: 2018/11/08 20:58:05 by ihuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_entry		*mkent(char *path)
{
	struct stat		st;
	t_entry			*new;

	new = (t_entry*)malloc(sizeof(t_entry));
	new->name = ft_strdup(path);
	if (lstat(new->name, &st) == 0)
	{
		new->mode = st.st_mode;
		new->nlink = st.st_nlink;
		new->uid = st.st_uid;
		new->gid = st.st_gid;
		new->size = st.st_size;
		new->mtimespec = st.st_mtimespec;
		new->blocks = st.st_blocks;
	}
	else
	{
		perror(new->name);
		free(new->name);
		free(new);
		new = NULL;
	}
	return (new);
}

/* 
** changed mkdir_ll first parameter to a char *
** this is so that we can customaize the path name
*/

t_ll		*mkdir_cont(char *dir_path, t_params *p)
{
	DIR				*dirp;
	struct dirent	*direntp;
	t_ll			*ll_under;
	t_entry			*ent;
	char			*path;

	ll_under = NULL;
	if ((dirp = opendir(dir_path)))
	{
		while ((direntp = readdir(dirp)) != NULL)
		{
			path = make_path(dir_path, direntp->d_name); 
			if ((ent = mkent(path)) != NULL)
				append_sort(&ll_under, ent, p);
			free(path);
		}
		closedir(dirp);
	}
	else
		perror(dir_path);
	return (ll_under);
}

void		get_list(char **av, t_ll **file_ll, t_ll **dir_ll, t_params *p)
{
	t_entry		*ent;

	if (!*av)
	{
		ent = mkent(".");
		append_sort(dir_ll, ent, p);
	}
	else
	{
		while (*av)
		{
			if ((ent = mkent(*av++)) != NULL)
			{
				if (!S_ISDIR(ent->mode))
					append_sort(file_ll, ent, p);
				else
					append_sort(dir_ll, ent, p);
			}
		}
		if (p->rflag)
		{
			lstrev(file_ll);
			lstrev(dir_ll);
		}
	}
}
