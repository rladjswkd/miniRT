/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specular_tangent_bonus.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 19:59:42 by gyepark           #+#    #+#             */
/*   Updated: 2022/11/11 19:59:43 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPECULAR_TANGENT_BONUS_H
# define SPECULAR_TANGENT_BONUS_H
# include "structure_bonus.h"

t_vec	get_tangent_norm(t_obj obj, t_coord p, t_vec ray_dir);
#endif
