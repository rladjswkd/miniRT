/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cone.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 19:58:34 by gyepark           #+#    #+#             */
/*   Updated: 2022/11/11 19:58:34 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECT_CONE_H
# define INTERSECT_CONE_H
# include "structure.h"

int	intersect_cone(t_ray ray, t_cn cn, double *t);
#endif
