/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 19:56:13 by gyepark           #+#    #+#             */
/*   Updated: 2022/11/11 19:56:14 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structure.h"
#include "vector_operation.h"
#include "intersect_closest.h"
#include <math.h>

int	intersect_sphere(t_ray ray, t_sp sp, double *t)
{
	t_inter		inter;
	t_equation	eq;
	t_vec		ray_sp;
	double		ret;

	ray_sp = vec_sub(ray.pos, sp.coord);
	eq.a = vec_dot(ray.dir, ray.dir);
	eq.b = 2 * vec_dot(ray_sp, ray.dir);
	eq.c = vec_dot(ray_sp, ray_sp) - pow(sp.diameter / 2, 2);
	solve_equation(eq, &inter);
	ret = choose_smaller_t(HUGE_VAL, inter.l, (1 < inter.l));
	ret = choose_smaller_t(ret, inter.r, (1 < inter.r));
	*t = ret;
	return (ret != HUGE_VAL);
}
