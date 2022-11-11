/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cone.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 19:56:01 by gyepark           #+#    #+#             */
/*   Updated: 2022/11/11 19:56:02 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structure.h"
#include "vector_operation.h"
#include "intersect_closest.h"
#include <math.h>

static void	cal_cn_body(t_ray ray, t_cn cn, t_inter *inter)
{
	t_equation	eq;
	t_vec		vec_dir;
	t_vec		vec_pos;
	t_vec		cn_ray;
	double		theta;

	theta = pow((cn.diameter / 2.0) / cn.height, 2);
	vec_dir = vec_sub(ray.dir, vec_scale(cn.norm, vec_dot(ray.dir, cn.norm)));
	cn_ray = vec_sub(
			ray.pos, vec_add(cn.coord, vec_scale(cn.norm, cn.height)));
	vec_pos = vec_sub(cn_ray, vec_scale(cn.norm, vec_dot(cn_ray, cn.norm)));
	eq.a = vec_dot(
			vec_dir, vec_dir) - theta * pow(vec_dot(ray.dir, cn.norm), 2);
	eq.b = 2.0 * vec_dot(vec_dir, vec_pos) - \
		2.0 * theta * vec_dot(ray.dir, cn.norm) * vec_dot(cn_ray, cn.norm);
	eq.c = vec_dot(
			vec_pos, vec_pos) - theta * pow(vec_dot(cn_ray, cn.norm), 2);
	solve_equation(eq, inter);
}

static void	cal_cn_caps(t_ray ray, t_cn cn, double *t3)
{
	double	n_dot_dir;

	n_dot_dir = vec_dot(cn.norm, ray.dir);
	*t3 = vec_dot(cn.norm, vec_sub(cn.coord, ray.pos)) / n_dot_dir;
}

int	intersect_cone(t_ray ray, t_cn cn, double *t)
{
	t_inter		t_1_2;
	double		t3;
	double		ret;

	cal_cn_body(ray, cn, &t_1_2);
	cal_cn_caps(ray, cn, &t3);
	ret = choose_smaller_t(HUGE_VAL, t_1_2.l, is_valid_t1t2(cn, ray, t_1_2.l));
	ret = choose_smaller_t(ret, t_1_2.r, is_valid_t1t2(cn, ray, t_1_2.r));
	ret = choose_smaller_t(ret, t3, is_valid_t3(cn, ray, t3));
	*t = ret;
	return (ret != HUGE_VAL);
}
