/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihuang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 22:54:33 by ihuang            #+#    #+#             */
/*   Updated: 2018/11/08 22:39:34 by ihuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef B_LS_H
# define B_LS_H

# include "libft/libft.h"
# include <sys/stat.h>
# include <sys/types.h>
# include <dirent.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <unistd.h>

typedef struct		s_params
{
	int				lflag;
	int				aflag;
	int				tflag;
	int				rflag;
	int				Rflag;
	int				count;
}					t_params;

typedef struct		s_entry
{
	char			*name;
	mode_t			mode;
	nlink_t			nlink;
	uid_t			uid;
	gid_t			gid;
	off_t			size;
	struct timespec mtimespec;
	quad_t			blocks;
}					t_entry;

typedef struct		s_ll
{
	t_entry			*ent;
	struct s_ll		*next;
}					t_ll;

void				ls(t_entry *ent, t_params *pp);
char				*create_modestring(t_entry *ent, char *mode);
void				print_total(t_ll *head, t_params *p);
void				print_path(char *path);
void				print_time(struct timespec ts);

void				print_all(t_ll *file_ll, t_ll *dir_ll, t_params *p);
void				print_recursively(t_ll *dir_ll, t_params *p);
void				print_ll(t_ll *head, t_params *p);
t_ll				*print_dirll(t_ll *head, int multiple, t_params *p);

int					ft_timecmp(t_ll *new, t_ll *ptr);
void				lstrev(t_ll **head);
t_ll				*create_node(t_entry *ent);
void				append(t_ll **list, t_ll *new);
void				append_sort(t_ll **list, t_entry *ent, t_params *p);

void				get_list(char **av, t_ll **file_ll, t_ll **dir_ll, t_params *p);
t_entry				*mkent(char *path);
t_ll				*mkdir_cont(char *dir_path, t_params *p);

t_params			*initiate_params(void);
char				get_params(char **av, t_params **p);
void				add_param(char c, t_params *p);

void				print_illegal_option(char c);
char				*make_path(char *big, char *small);
void				print_dir_name(char *dir_name);

void				free_ll(t_ll **head);

#endif
