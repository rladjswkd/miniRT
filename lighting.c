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

t_vec	compute_specular(t_vec inter, t_vec n, t_vec v, t_light light)
{
	t_vec	ret;
	t_vec	l;
	t_vec	r;
	double	r_dot_v;

	ret = (t_vec){0, 0, 0};
	l = vec_normalize(vec_sub(light.coord, inter));
	r = vec_sub(vec_neg(l), vec_scale(n, 2.0 * vec_dot(n, vec_neg(l))));
	r_dot_v = vec_dot(v, r);
	if (r_dot_v > 0)
		ret = vec_scale(rgb_to_vec(light.rgb), \
			light.intensity * pow(r_dot_v, S_EXP));
	return (ret);
}

static t_vec	lower_to_one(t_vec lighting)
{
	lighting.x -= (lighting.x > 1.0) * (lighting.x - 1.0);
	lighting.y -= (lighting.y > 1.0) * (lighting.y - 1.0);
	lighting.z -= (lighting.z > 1.0) * (lighting.z - 1.0);
	return (lighting);
}

t_vec	compute_lighting(t_vec inter, t_vec n, t_vec v, t_world world)
{
	t_vec	v_ambient;
	t_vec	v_diffuse;
	t_vec	v_specular;
	t_node	*l;

	l = world.l;
	v_ambient = vec_scale(rgb_to_vec(world.a.rgb), world.a.intensity);
	v_diffuse = (t_vec){0, 0, 0};
	v_specular = (t_vec){0, 0, 0};
	while (l)
	{	
		if (!check_shadow(world, get_l_ray(*(t_light *)l->data, inter)))
		{
			v_diffuse = vec_add(v_diffuse,
					compute_diffuse(inter, n, *(t_light *)l->data));
			v_specular = vec_add(v_specular,
					compute_specular(inter, n, v, *(t_light *)l->data));
		}
		l = l->next;
	}
	return (lower_to_one(vec_add(vec_add(v_ambient, v_diffuse), v_specular)));
}
