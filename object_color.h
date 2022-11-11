/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_color.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 19:59:14 by gyepark           #+#    #+#             */
/*   Updated: 2022/11/11 19:59:15 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_COLOR_H
# define OBJECT_COLOR_H
# include "structure.h"

t_rgb	get_obj_rgb(t_vars *vars, t_obj obj, t_coord p, t_vec lighting);
#endif
