/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 19:56:22 by gyepark           #+#    #+#             */
/*   Updated: 2022/11/11 19:56:23 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structure.h"
#include "allocator.h"
#include <stdlib.h>

int	alloc_new_node(t_node **node, int index)
{
	static int	(*allocator[5])(void **)
		= {alloc_light, alloc_sphere, alloc_plane, alloc_cylinder, alloc_cone};

	*node = (t_node *)malloc(sizeof(t_node));
	if (!(*node))
		return (0);
	(*node)->next = 0;
	if (!(*allocator[index - 2])(&((*node)->data)))
	{
		free(*node);
		return (0);
	}
	return (1);
}

void	append_node(t_node **lst, t_node *new)
{
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	while ((*lst)->next)
		lst = &((*lst)->next);
	(*lst)->next = new;
}

t_node	*get_last_node(t_node *list)
{
	while (list->next)
		list = list->next;
	return (list);
}

void	clear_list(t_node **lst)
{
	t_node	*next;

	while (*lst)
	{
		next = (*lst)->next;
		free((*lst)->data);
		free(*lst);
		*lst = next;
	}
	*lst = 0;
}
