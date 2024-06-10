/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec4_operations.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 20:00:03 by gyepark           #+#    #+#             */
/*   Updated: 2022/11/11 20:00:03 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC4_OPERATIONS_H
# define VEC4_OPERATIONS_H
# include "structure.h"

double	vec4_dot(t_vec4 v1, t_vec4 v2);
t_vec	vec4_to_vec(t_vec4 v);
t_vec4	vec_to_vec4(t_vec v);
t_vec4	arr_to_vec4(double arr[4]);
#endif
