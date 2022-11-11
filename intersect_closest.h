/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_closest.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 19:58:32 by gyepark           #+#    #+#             */
/*   Updated: 2022/11/11 19:58:32 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECT_CLOSEST_H
# define INTERSECT_CLOSEST_H
# include "structure.h"

double	choose_smaller_t(double current, double candidate, int condition);
void	solve_equation(t_equation eq, t_inter *inter);
int		is_valid_t1t2(t_cy cy, t_ray ray, double t);
int		is_valid_t3(t_cy cy, t_ray ray, double t);
int		is_valid_t4(t_cy cy, t_ray ray, double t);
#endif
