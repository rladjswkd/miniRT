/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operation_bonus.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 20:00:09 by gyepark           #+#    #+#             */
/*   Updated: 2022/11/11 20:03:08 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_OPERATION_BONUS_H
# define VECTOR_OPERATION_BONUS_H
# include "structure_bonus.h"

t_vec	vec_add(t_vec v1, t_vec v2);
t_vec	vec_sub(t_vec v1, t_vec v2);
t_vec	vec_scale(t_vec vec, double scalar);
t_vec	vec_neg(t_vec vec);
double	vec_dot(t_vec v1, t_vec v2);
t_vec	vec_cross(t_vec v1, t_vec v2);
double	vec_len(t_vec vec);
t_vec	vec_normalize(t_vec vec);
t_vec	vec_proj(t_vec v1, t_vec v2);
#endif
