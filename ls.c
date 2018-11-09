/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihuang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/04 10:51:19 by ihuang            #+#    #+#             */
/*   Updated: 2018/11/08 22:39:36 by ihuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ls(t_entry *ent, t_params *pp)
{
	char			*buf;
	char			*ptr;
	struct group	*gr;
	struct passwd	*pw;

	ptr = ft_strrchr(ent->name, '/');
	if ((!pp->aflag) && (ptr && *(ptr + 1) == '.'))
		return ;
	if (pp->lflag)
	{
		buf = (char*)malloc(sizeof(char) * 200);
		printf("%s ", create_modestring(ent, buf));
		printf("%3d ", ent->nlink);
		if ((pw = getpwuid(ent->uid)))
			printf("%s  ", pw->pw_name);
		if ((gr = getgrgid(ent->gid)))
			printf("%s  %5lld ", gr->gr_name, ent->size);
		print_time(ent->mtimespec);
		free(buf);
	}
	if (ptr)
		printf("%s", (ptr + 1));
	else
		printf("%s", ent->name);
	if (pp->lflag && S_ISLNK(ent->mode))
		print_path(ent->name);
	printf("\n");
}

char		*create_modestring(t_entry *ent, char *mode)
{
	*mode = '-';
	if (S_ISLNK(ent->mode))
		*mode = 'l';
	else if (S_ISDIR(ent->mode))
		*mode = 'd';
	*++mode = ((ent->mode & S_IRUSR) ? 'r' : '-');
	*++mode = ((ent->mode & S_IWUSR) ? 'w' : '-');
	*++mode = ((ent->mode & S_IXUSR) ? 'x' : '-');
	*mode = ((ent->mode & S_ISUID) ? 'S' : *mode);
	*++mode = ((ent->mode & S_IRGRP) ? 'r' : '-');
	*++mode = ((ent->mode & S_IWGRP) ? 'w' : '-');
	*++mode = ((ent->mode & S_IXGRP) ? 'x' : '-');
	*mode = ((ent->mode & S_ISGID) ? 'S' : *mode);
	*++mode = ((ent->mode & S_IROTH) ? 'r' : '-');
	*++mode = ((ent->mode & S_IWOTH) ? 'w' : '-');
	*++mode = ((ent->mode & S_IXOTH) ? 'x' : '-');
	*mode = ((ent->mode & S_ISVTX) ? 'T' : *mode);
	*++mode = '\0';
	return (mode - 10);
}

void		print_total(t_ll *head, t_params *p)
{
	unsigned int	total;
	char			*ptr;

	total = 0;
	while (head)
	{
		ptr = ft_strrchr(head->ent->name, '/');
		if (!p->aflag && ptr && *(ptr + 1) == '.')
		{
			head = head->next;
			continue ;
		}
		total += head->ent->blocks;
		head = head->next;
	}
	if (total)
		printf("total %u\n", total);
}

void		print_path(char *path)
{
	char			*buf;
	int				len;

	len = 0;
	if ((buf = (char*)malloc(sizeof(char) * 100)) != NULL)
	{
		if ((len = readlink(path, buf, 100)) != -1)
		{
			*(buf + len) = '\0';
			printf(" -> %s", buf);
		}
		else
			perror(path);
		free(buf);
	}
}

void		print_time(struct timespec ts)
{
	char		*s;

	if (time(NULL) > ts.tv_sec + (180 * 24 * 60 * 60) || \
			time(NULL) < ts.tv_sec)
	{
		s = ctime(&(ts.tv_sec)) + 4;
		printf("%.6s  ", s);
		s += 16;
		printf("%.4s ", s);
	}
	else
	{
		s = ctime(&(ts.tv_sec)) + 4;
		printf("%.12s ", s);
	}
}
