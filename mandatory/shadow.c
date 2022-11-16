/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 19:57:02 by gyepark           #+#    #+#             */
/*   Updated: 2022/11/11 19:57:03 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structure.h"
#include "intersect_cylinder.h"
#include "intersect_sphere.h"
#include "intersect_plane.h"

static int	check_shadow_sp(t_ray ray, t_node *sp)
{
	double	cur;

	cur = 2;
	if (!sp)
		return (0);
	while (sp)
	{
		if (intersect_sphere(ray, *((t_sp *)(sp->data)), &cur) && cur < 2)
			return (1);
		sp = sp->next;
	}
	return (0);
}

static int	check_shadow_cy(t_ray ray, t_node *cy)
{
	double	cur;

	cur = 2;
	if (!cy)
		return (0);
	while (cy)
	{
		if (intersect_cylinder(ray, *((t_cy *)(cy->data)), &cur) && cur < 2)
			return (1);
		cy = cy->next;
	}
	return (0);
}

static int	check_shadow_pl(t_ray ray, t_node *pl)
{
	double	cur;

	cur = 2;
	if (!pl)
		return (0);
	while (pl)
	{
		if (intersect_plane(ray, *((t_pl *)(pl->data)), &cur) && cur < 2)
			return (1);
		pl = pl->next;
	}
	return (0);
}

int	check_shadow(t_world world, t_ray l_ray)
{
	if (check_shadow_sp(l_ray, world.sp))
		return (1);
	if (check_shadow_cy(l_ray, world.cy))
		return (1);
	if (check_shadow_pl(l_ray, world.pl))
		return (1);
	return (0);
}
