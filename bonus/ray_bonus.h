/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 19:59:22 by gyepark           #+#    #+#             */
/*   Updated: 2022/11/11 19:59:23 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_BONUS_H
# define RAY_BONUS_H
# include "structure_bonus.h"

t_ray	get_l_ray(t_light l, t_vec p);
int		trace_ray(t_vars *vars, t_world *world, t_ray ray, int i);
t_ray	generate_ray(t_coord pos, t_viewport viewport, int i, int j);
#endif
