/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 19:58:37 by gyepark           #+#    #+#             */
/*   Updated: 2022/11/11 19:58:37 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECT_CYLINDER_H
# define INTERSECT_CYLINDER_H
# include "structure.h"

int	intersect_cylinder(t_ray ray, t_cy cy, double *t);
#endif
