/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 19:56:20 by gyepark           #+#    #+#             */
/*   Updated: 2022/11/11 19:56:20 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structure.h"
#include "constant.h"
#include "vector_operation.h"
#include "shadow.h"
#include "ray.h"
#include <math.h>

static t_vec	rgb_to_vec(t_rgb rgb)
{
	return ((t_vec){rgb.r / 255.0, rgb.g / 255.0, rgb.b / 255.0});
}

t_vec	compute_diffuse(t_vec inter, t_vec n, t_light light)
{
	t_vec	ret;
	t_vec	l;
	double	n_dot_l;

	ret = (t_vec){0, 0, 0};
	l = vec_normalize(vec_sub(light.coord, inter));
	n_dot_l = vec_dot(n, l);
	if (n_dot_l > 0)
		ret = vec_scale(rgb_to_vec(light.rgb), light.intensity * n_dot_l);
	return (ret);
}

static t_vec	lower_to_one(t_vec lighting)
{
	lighting.x -= (lighting.x > 1.0) * (lighting.x - 1.0);
	lighting.y -= (lighting.y > 1.0) * (lighting.y - 1.0);
	lighting.z -= (lighting.z > 1.0) * (lighting.z - 1.0);
	return (lighting);
}

t_vec	compute_lighting(t_vec inter, t_vec n, t_world world)
{
	t_vec	v_ambient;
	t_vec	v_diffuse;

	v_ambient = vec_scale(rgb_to_vec(world.a.rgb), world.a.intensity);
	v_diffuse = (t_vec){0, 0, 0};
	if (!check_shadow(world, get_l_ray(world.l, inter)))
		v_diffuse = vec_add(v_diffuse,
				compute_diffuse(inter, n, world.l));
	return (lower_to_one(vec_add(v_ambient, v_diffuse)));
}
