/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_world.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 19:56:57 by gyepark           #+#    #+#             */
/*   Updated: 2022/11/11 19:57:00 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structure.h"
#include "linked_list.h"
#include "set_essential.h"
#include "set_additional.h"
#include "set_world.h"
#include "parser_util_split.h"
#include "checker.h"
#include <stdlib.h>

static int	set_object_list(t_world *rt, int index)
{
	t_node	**objects;
	t_node	*new_node;

	if (!alloc_new_node(&new_node, index))
		return (0);
	objects = &(rt->l);
	if (index == 3)
		objects = &(rt->sp);
	else if (index == 4)
		objects = &(rt->pl);
	else if (index == 5)
		objects = &(rt->cy);
	else if (index == 6)
		objects = &(rt->cn);
	append_node(objects, new_node);
	return (1);
}

int	set_world(char *line, t_world *rt, int *mask)
{
	char		**splitted;
	int			cnt;
	int			index;
	static int	(*fp[7])(char **, int, t_world *) = {set_ambient, set_camera,
		set_light, set_sphere, set_plane, set_cylinder, set_cylinder};

	splitted = split_line(line, ' ', &cnt);
	if (!(splitted && splitted[0]))
		return (free_splitted(splitted, 0));
	index = check_identifier(splitted[0]);
	if (index == -1)
		return (free_splitted(splitted, 0));
	if (index < 2 && (*mask & 1 << index || !(*fp[index])(splitted, cnt, rt)))
		return (free_splitted(splitted, 0));
	*mask |= 1 << index;
	if (1 < index
		&& (!set_object_list(rt, index) || !(*fp[index])(splitted, cnt, rt)))
		return (free_splitted(splitted, 0));
	return (free_splitted(splitted, 1));
}

int	free_splitted(char **splitted, int ret)
{
	int	i;

	i = -1;
	while (splitted[++i])
		free(splitted[i]);
	free(splitted);
	return (ret);
}
