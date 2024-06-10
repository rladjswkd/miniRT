/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv_mapper_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 19:57:12 by gyepark           #+#    #+#             */
/*   Updated: 2022/11/11 19:57:13 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structure_bonus.h"
#include "vector_operation_bonus.h"
#include "object_pattern_bonus.h"
#include <math.h>

t_uv	uv_map_sphere(t_coord p, t_sp sp)
{
	t_uv	uv;
	t_vec	vec;

	vec = vec_normalize(vec_sub(p, sp.coord));
	uv.u = 1 - (0.5 + atan2(vec.x, vec.y) / (2 * M_PI));
	uv.v = 0.5 - asin(vec.z) / M_PI;
	uv.pu = vec_normalize(vec_cross(vec, get_basis_vec(vec)));
	uv.pv = vec_normalize(vec_cross(vec, uv.pu));
	return (uv);
}

t_uv	uv_map_plane(t_coord p, t_pl pl)
{
	t_vec	e1;
	t_vec	e2;
	double	u;
	double	v;

	e1 = vec_cross(pl.norm, get_basis_vec(pl.norm));
	e2 = vec_cross(pl.norm, e1);
	u = fmod(vec_dot(p, e1), 100);
	v = fmod(vec_dot(p, e2), 100);
	u = 100 * (u < 0) + u;
	v = 100 * (v < 0) + v;
	return ((t_uv){u / 100, v / 100,
		vec_normalize(e1),
		vec_normalize(e2)});
}

t_uv	uv_map_cylinder(t_coord p, t_cy cy)
{
	t_vec	e1;
	t_vec	e2;
	t_uv	uv;
	t_vec	c_p;
	t_vec	n_p;

	e1 = vec_cross(cy.norm, get_basis_vec(cy.norm));
	e2 = vec_cross(cy.norm, e1);
	c_p = vec_sub(p, cy.coord);
	uv.u = 0.5 + atan2(vec_dot(c_p, e1), vec_dot(c_p, e2)) / (2 * M_PI);
	uv.v = vec_len(vec_proj(vec_sub(p, cy.coord), cy.norm)) / (cy.height + 1);
	n_p = vec_normalize(vec_sub(p, vec_add(cy.coord, vec_proj(c_p, cy.norm))));
	if (vec_dot(c_p, cy.norm))
		n_p = cy.norm;
	uv.pu = vec_normalize(vec_cross(n_p, get_basis_vec(n_p)));
	uv.pv = vec_normalize(vec_cross(n_p, uv.pu));
	return (uv);
}

t_vec	get_cone_body_norm(t_coord p, t_cn cn)
{
	t_coord	x;
	double	len_top_x;
	double	theta;

	theta = atan2(cn.diameter / 2, cn.height);
	len_top_x = vec_len(vec_sub(p, vec_add(p, vec_scale(cn.norm, cn.height))))
		/ cos(theta);
	x = vec_add(cn.coord, vec_scale(cn.norm, cn.height - len_top_x));
	return (vec_normalize(vec_sub(p, x)));
}

t_uv	uv_map_cone(t_coord p, t_cn cn)
{
	t_uv	ret;
	t_vec	n_p;

	ret = uv_map_cylinder(p, (t_cy)cn);
	n_p = get_cone_body_norm(p, cn);
	ret.pu = vec_normalize(vec_cross(n_p, get_basis_vec(n_p)));
	ret.pv = vec_normalize(vec_cross(n_p, ret.pu));
	return (ret);
}
