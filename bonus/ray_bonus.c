/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 19:56:50 by gyepark           #+#    #+#             */
/*   Updated: 2022/11/11 19:56:50 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structure_bonus.h"
#include "constant_bonus.h"
#include "vector_operation_bonus.h"
#include "intersect_world_bonus.h"
#include "specular_tangent_bonus.h"
#include "object_color_bonus.h"
#include "lighting_bonus.h"
#include "normal_transformation_bonus.h"

t_ray	get_l_ray(t_light l, t_vec p)
{
	t_ray	l_ray;

	l_ray.dir = vec_sub(l.coord, p);
	l_ray.pos = vec_sub(p, l_ray.dir);
	l_ray.dir = vec_scale(l_ray.dir, SHADOW_BIAS);
	return (l_ray);
}

static int	get_status(int type, void *object)
{
	if (type == SPHERE)
		return (((t_sp *)object)->status);
	if (type == CYLINDER)
		return (((t_cy *)object)->status);
	if (type == PLANE)
		return (((t_pl *)object)->status);
	return (((t_cn *)object)->status);
}

static void	dot_pixel(t_img *img, t_rgb color, int i)
{
	int		pixel;

	pixel = i * 4;
	img->addr[pixel] = color.b;
	img->addr[pixel + 1] = color.g;
	img->addr[pixel + 2] = color.r;
}

int	trace_ray(t_vars *vars, t_world *world, t_ray ray, int i)
{
	t_obj	obj;
	t_rgb	color;
	t_coord	p;
	t_vec	n;

	if (!intersect(ray, *world, &obj))
		color = (t_rgb){0, 0, 0};
	else
	{
		p = vec_add(ray.pos, vec_scale(ray.dir, obj.t));
		n = get_tangent_norm(obj, p, ray.dir);
		if (get_status(obj.type, obj.object) & BUMP)
			n = get_bump_norm(vars, obj, p, n);
		color = get_obj_rgb(vars, obj, p, compute_lighting(
					p, n, vec_neg(vec_normalize(ray.dir)), *world));
	}
	dot_pixel(&vars->img, color, i);
	return (0);
}

t_ray	generate_ray(t_coord pos, t_viewport viewport, int i, int j)
{
	t_ray	ret;
	t_coord	tmp;

	ret.pos = pos;
	tmp = viewport.top_left;
	tmp = vec_add(tmp, vec_scale(viewport.v_width, i));
	tmp = vec_add(tmp, vec_scale(viewport.v_height, j));
	ret.dir = vec_sub(tmp, pos);
	return (ret);
}
