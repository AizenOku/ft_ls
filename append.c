/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihuang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/04 10:02:49 by ihuang            #+#    #+#             */
/*   Updated: 2018/11/04 10:58:11 by ihuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			ft_timecmp(t_ll *new, t_ll *ptr)
{
	if (new->ent->mtimespec.tv_sec == ptr->ent->mtimespec.tv_sec)
	{
		if (new->ent->mtimespec.tv_nsec == ptr->ent->mtimespec.tv_nsec)
			return (-1 * ft_strcmp(new->ent->name, ptr->ent->name));
		else
			return (new->ent->mtimespec.tv_nsec - ptr->ent->mtimespec.tv_nsec);
	}
	return (new->ent->mtimespec.tv_sec - ptr->ent->mtimespec.tv_sec);
}

void		lstrev(t_ll **head)
{
	t_ll	*curr;
	t_ll	*prev;
	t_ll	*next;

	curr = *head;
	prev = NULL;
	next = NULL;
	if (!*head)
		return ;
	while (curr)
	{
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	*head = prev;
}

t_ll		*create_node(t_entry *ent)
{
	t_ll		*new;

	new = NULL;
	if ((new = malloc(sizeof(*new))))
	{
		new->ent = ent;
		new->next = NULL;
	}
	return (new);
}

void		append(t_ll **head, t_ll *new)
{
	t_ll			*ptr;
	
	ptr = *head;
	if (*head == NULL)
		return ;
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = new;
}

/*
** append_sort(&list, ent, p) takes in a list address,
** entry pointer, and params pointer
** it first creates a new node based on ent
** then, inserts the new node into the list based on whichever order the sorting is
**
** sorting: while there is something to be compared
** and the new is not yet in position,
** move position
*/

void		append_sort(t_ll **list, t_entry *ent, t_params *p)
{
	t_ll		*new;
	t_ll		*ptr;
	t_ll		*prev;

	new = create_node(ent);
	prev = NULL;
	ptr = *list;
	while (ptr)
	{
		if (p->tflag)
		{
			if (ft_timecmp(new, ptr) > 0)
				break ;
		}
		else if (ft_strcmp(new->ent->name, ptr->ent->name) < 0)
			break ;
		prev = ptr;
		ptr = ptr->next;
	}
	new->next = ptr;
	if (prev)
		prev->next = new;
	if (*list == NULL || prev == NULL)
		*list = new;
}
