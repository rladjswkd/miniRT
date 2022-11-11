/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specular_tangent.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 19:59:42 by gyepark           #+#    #+#             */
/*   Updated: 2022/11/11 19:59:43 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPECULAR_TANGENT_H
# define SPECULAR_TANGENT_H
# include "structure.h"

t_vec	get_tangent_norm(t_obj obj, t_coord p, t_vec ray_dir);
#endif
