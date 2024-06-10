/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_sphere.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 19:58:43 by gyepark           #+#    #+#             */
/*   Updated: 2022/11/11 19:58:43 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECT_SPHERE_H
# define INTERSECT_SPHERE_H
# include "structure.h"

int	intersect_sphere(t_ray ray, t_sp sp, double *t);
#endif
