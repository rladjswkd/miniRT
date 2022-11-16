/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv_mapper_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 20:00:00 by gyepark           #+#    #+#             */
/*   Updated: 2022/11/11 20:00:01 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UV_MAPPER_BONUS_H
# define UV_MAPPER_BONUS_H
# include "structure_bonus.h"

t_uv	uv_map_sphere(t_coord p, t_sp sp);
t_uv	uv_map_plane(t_coord p, t_pl pl);
t_uv	uv_map_cylinder(t_coord p, t_cy cy);
t_vec	get_cone_body_norm(t_coord p, t_cn cn);
t_uv	uv_map_cone(t_coord p, t_cn cn);
#endif
