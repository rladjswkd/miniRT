/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 19:56:04 by gyepark           #+#    #+#             */
/*   Updated: 2022/11/11 19:56:05 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structure.h"
#include "vector_operation.h"
#include "intersect_closest.h"
#include <math.h>

static void	cal_cy_body(t_ray ray, t_cy cy, t_inter *inter)
{
	t_equation	eq;
	t_vec		vec_dir;
	t_vec		vec_pos;
	t_vec		cy_ray;

	vec_dir = vec_sub(ray.dir, vec_scale(cy.norm, vec_dot(ray.dir, cy.norm)));
	cy_ray = vec_sub(ray.pos, cy.coord);
	vec_pos = vec_sub(cy_ray, vec_scale(cy.norm, vec_dot(cy_ray, cy.norm)));
	eq.a = vec_dot(vec_dir, vec_dir);
	eq.b = 2 * vec_dot(vec_dir, vec_pos);
	eq.c = vec_dot(vec_pos, vec_pos) - pow(cy.diameter / 2, 2);
	solve_equation(eq, inter);
}

static void	cal_cy_caps(t_ray ray, t_cy cy, t_inter *inter)
{
	t_vec	bottom_center;
	t_vec	top_center;
	double	n_dot_dir;

	bottom_center = cy.coord;
	top_center = vec_add(cy.coord, vec_scale(cy.norm, cy.height));
	n_dot_dir = vec_dot(cy.norm, ray.dir);
	inter->l = vec_dot(cy.norm, vec_sub(bottom_center, ray.pos)) / n_dot_dir;
	inter->r = vec_dot(cy.norm, vec_sub(top_center, ray.pos)) / n_dot_dir;
}

int	intersect_cylinder(t_ray ray, t_cy cy, double *t)
{
	t_inter		t_1_2;
	t_inter		t_3_4;
	double		ret;

	cal_cy_body(ray, cy, &t_1_2);
	cal_cy_caps(ray, cy, &t_3_4);
	ret = choose_smaller_t(HUGE_VAL, t_1_2.l, is_valid_t1t2(cy, ray, t_1_2.l));
	ret = choose_smaller_t(ret, t_1_2.r, is_valid_t1t2(cy, ray, t_1_2.r));
	ret = choose_smaller_t(ret, t_3_4.l, is_valid_t3(cy, ray, t_3_4.l));
	ret = choose_smaller_t(ret, t_3_4.r, is_valid_t4(cy, ray, t_3_4.r));
	*t = ret;
	return (ret != HUGE_VAL);
}
