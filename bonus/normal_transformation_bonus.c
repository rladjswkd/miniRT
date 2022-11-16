/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_transformation_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 19:56:41 by gyepark           #+#    #+#             */
/*   Updated: 2022/11/11 19:56:41 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structure_bonus.h"
#include "constant_bonus.h"
#include "uv_mapper_bonus.h"
#include "matrix_transformation_bonus.h"
#include "vec4_operations_bonus.h"
#include "matrix_multiplication_bonus.h"
#include "matrix_transpose_bonus.h"
#include "vector_operation_bonus.h"

t_vec	rotate_normal(t_vec vec, t_mat op)
{
	t_mat	rx;
	t_mat	ry;
	t_vec4	res;

	rx = get_rx_to_z(vec);
	res = mat_mul_vec4(rx, vec_to_vec4(vec));
	ry = get_ry_to_z(vec4_to_vec(res));
	res = mat_mul_vec4(ry, res);
	res = mat_mul_vec4(op, res);
	res = mat_mul_vec4(mat_transpose(ry), res);
	res = mat_mul_vec4(mat_transpose(rx), res);
	return (vec4_to_vec(res));
}

t_vec	get_bump_norm(t_vars *vars, t_obj obj, t_vec p, t_vec n)
{
	t_vec	ret;
	t_uv	uv;
	int		i;
	double	bu;
	double	bv;

	ret = (t_vec){0, 0, 0};
	if (obj.type == SPHERE)
		uv = uv_map_sphere(p, *(t_sp *)obj.object);
	else if (obj.type == CYLINDER)
		uv = uv_map_cylinder(p, *(t_cy *)obj.object);
	else if (obj.type == PLANE)
		uv = uv_map_plane(p, *(t_pl *)obj.object);
	else if (obj.type == CONE)
		uv = uv_map_cone(p, *(t_cn *)obj.object);
	i = vars->b_img.width * uv.u
		+ (int)(vars->b_img.height * uv.v) * vars->b_img.width;
	bu = vars->b_img.addr[i * 4] - vars->b_img.addr[(i + 1) * 4];
	bv = vars->b_img.addr[i * 4]
		- vars->b_img.addr[(vars->b_img.width + i) * 4];
	bu /= BUMP_HIGHT_WEIGHT;
	bv /= BUMP_HIGHT_WEIGHT;
	ret = vec_sub(vec_scale(vec_cross(n, uv.pv), bu),
			vec_scale(vec_cross(n, uv.pu), bv));
	return (vec_normalize(vec_add(n, ret)));
}
