/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_world.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 19:58:45 by gyepark           #+#    #+#             */
/*   Updated: 2022/11/11 19:58:45 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECT_WORLD_H
# define INTERSECT_WORLD_H
# include "structure.h"

int	intersect(t_ray ray, t_world world, t_obj *obj);
#endif
