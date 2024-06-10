/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operation_1_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 20:07:33 by gyepark           #+#    #+#             */
/*   Updated: 2022/11/11 20:07:34 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_operation_bonus.h"

t_vec	vec_add(t_vec v1, t_vec v2)
{
	return ((t_vec){v1.x + v2.x, v1.y + v2.y, v1.z + v2.z});
}

t_vec	vec_sub(t_vec v1, t_vec v2)
{
	return ((t_vec){v1.x - v2.x, v1.y - v2.y, v1.z - v2.z});
}

t_vec	vec_scale(t_vec vec, double scalar)
{
	return ((t_vec){vec.x * scalar, vec.y * scalar, vec.z * scalar});
}

t_vec	vec_neg(t_vec vec)
{
	return ((t_vec){-vec.x, -vec.y, -vec.z});
}
