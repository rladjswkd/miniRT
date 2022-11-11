/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_plane.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 19:58:40 by gyepark           #+#    #+#             */
/*   Updated: 2022/11/11 19:58:41 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECT_PLANE_H
# define INTERSECT_PLANE_H
# include "structure.h"

int	intersect_plane(t_ray ray, t_pl pl, double *t);
#endif
