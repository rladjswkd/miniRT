/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_closest.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 19:55:58 by gyepark           #+#    #+#             */
/*   Updated: 2022/11/11 19:55:59 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structure.h"
#include "vector_operation.h"
#include <math.h>

double	choose_smaller_t(double current, double candidate, int condition)
{
	if (condition && candidate < current)
		return (candidate);
	return (current);
}

void	solve_equation(t_equation eq, t_inter *inter)
{
	double	d;

	d = eq.b * eq.b - 4 * eq.a * eq.c;
	if (d < 0)
	{
		inter->l = HUGE_VAL;
		inter->r = HUGE_VAL;
		return ;
	}
	inter->l = (-eq.b - sqrt(d)) / (2 * eq.a);
	inter->r = (-eq.b + sqrt(d)) / (2 * eq.a);
}

int	is_valid_t1t2(t_cy cy, t_ray ray, double t)
{
	return (t > 1 && vec_dot(cy.norm, vec_sub(
				vec_add(ray.pos, vec_scale(ray.dir, t)), cy.coord)) > 0
		&& vec_dot(cy.norm, vec_sub(
				vec_add(ray.pos, vec_scale(ray.dir, t)),
				vec_add(cy.coord, vec_scale(cy.norm, cy.height)))) < 0);
}

int	is_valid_t3(t_cy cy, t_ray ray, double t)
{
	t_vec	q_to_cap;

	q_to_cap = vec_sub(vec_add(ray.pos, vec_scale(ray.dir, t)),
			cy.coord);
	return (t > 1 && vec_dot(q_to_cap, q_to_cap) < pow(cy.diameter / 2, 2));
}

int	is_valid_t4(t_cy cy, t_ray ray, double t)
{
	t_vec	q_to_cap;

	q_to_cap = vec_sub(vec_add(ray.pos, vec_scale(ray.dir, t)),
			vec_add(cy.coord, vec_scale(cy.norm, cy.height)));
	return (t > 1 && vec_dot(q_to_cap, q_to_cap) < pow(cy.diameter / 2, 2));
}
