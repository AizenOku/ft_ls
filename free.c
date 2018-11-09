/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihuang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 22:13:58 by ihuang            #+#    #+#             */
/*   Updated: 2018/11/08 19:36:37 by ihuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	free_ll(t_ll **head)
{
	t_ll	*ptr;
	t_ll	*next;

	next = NULL;
	if (*head == NULL)
		return ;
	ptr = *head;
	while (ptr)
	{
		next = ptr->next;
		free(ptr->ent->name);
		free(ptr->ent);
		free(ptr);
		ptr = next;
	}
	*head = NULL;
}
