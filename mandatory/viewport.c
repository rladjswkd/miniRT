/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 19:57:35 by gyepark           #+#    #+#             */
/*   Updated: 2022/11/11 19:57:36 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structure.h"
#include "constant.h"
#include "vector_operation.h"
#include "vec4_operations.h"
#include "matrix_multiplication.h"
#include "matrix_transformation.h"
#include <math.h>

t_vec	get_viewport_vec(t_camera c, t_vec4 axis)
{
	return (vec4_to_vec(mat_mul_vec4(
				mat_mul(rotate_longitude(c.longi), rotate_latitude(c.lati)),
				axis)));
}

t_viewport	generate_viewport(t_camera c)
{
	t_vec	v_w;
	t_vec	v_h;
	t_vec	top_left;
	double	vp_h;
	double	vp_w;

	vp_w = tan((c.fov * M_PI / 180.0) / 2.0) * 2;
	vp_h = vp_w * HEIGHT / WIDTH;
	v_w = vec_scale(get_viewport_vec(c, (t_vec4){0, -1, 0, 1}), vp_w / WIDTH);
	v_h = vec_scale(get_viewport_vec(c, (t_vec4){1, 0, 0, 1}), vp_h / HEIGHT);
	top_left = vec_add(c.coord, c.norm);
	top_left = vec_sub(top_left, vec_scale(v_w, WIDTH / 2.0));
	top_left = vec_sub(top_left, vec_scale(v_h, HEIGHT / 2.0));
	return ((t_viewport){top_left, v_w, v_h});
}
