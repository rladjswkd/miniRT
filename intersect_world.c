/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_world.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 19:56:16 by gyepark           #+#    #+#             */
/*   Updated: 2022/11/11 19:56:17 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structure.h"
#include "constant.h"
#include "intersect_cylinder.h"
#include "intersect_plane.h"
#include "intersect_sphere.h"
#include <math.h>

static void	check_sp(t_ray ray, t_node *sp, t_obj *obj)
{
	double	cur;
	double	t;

	if (!sp)
		return ;
	t = obj->t;
	while (sp)
	{
		if (intersect_sphere(ray, *((t_sp *)(sp->data)), &cur) && cur < t)
		{
			t = cur;
			obj->type = SPHERE;
			obj->object = (t_sp *)(sp->data);
		}
		sp = sp->next;
	}
	obj->t = t;
}

static void	check_cy(t_ray ray, t_node *cy, t_obj *obj)
{
	double	cur;
	double	t;

	if (!cy)
		return ;
	t = obj->t;
	while (cy)
	{
		if (intersect_cylinder(ray, *((t_cy *)(cy->data)), &cur) && cur < t)
		{
			t = cur;
			obj->type = CYLINDER;
			obj->object = (t_cy *)(cy->data);
		}
		cy = cy->next;
	}
	obj->t = t;
}

static void	check_pl(t_ray ray, t_node *pl, t_obj *obj)
{
	double	cur;
	double	t;

	if (!pl)
		return ;
	t = obj->t;
	while (pl)
	{
		if (intersect_plane(ray, *((t_pl *)(pl->data)), &cur) && cur < t)
		{
			t = cur;
			obj->type = PLANE;
			obj->object = (t_pl *)(pl->data);
		}
		pl = pl->next;
	}
	obj->t = t;
}

int	intersect(t_ray ray, t_world world, t_obj *obj)
{
	obj->type = NONE;
	obj->t = HUGE_VAL;
	check_sp(ray, world.sp, obj);
	check_cy(ray, world.cy, obj);
	check_pl(ray, world.pl, obj);
	return (obj->type);
}
