/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_world_bonus.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 19:58:45 by gyepark           #+#    #+#             */
/*   Updated: 2022/11/11 19:58:45 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECT_WORLD_BONUS_H
# define INTERSECT_WORLD_BONUS_H
# include "structure_bonus.h"

int	intersect(t_ray ray, t_world world, t_obj *obj);
#endif
