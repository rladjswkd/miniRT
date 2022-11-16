/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 20:00:11 by gyepark           #+#    #+#             */
/*   Updated: 2022/11/11 20:03:19 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIEWPORT_BONUS_H
# define VIEWPORT_BONUS_H
# include "structure_bonus.h"

t_vec		get_viewport_vec(t_camera c, t_vec4 axis);
t_viewport	generate_viewport(t_camera c);
#endif
