/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec4_operations_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 19:57:15 by gyepark           #+#    #+#             */
/*   Updated: 2022/11/11 19:57:16 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structure_bonus.h"

double	vec4_dot(t_vec4 v1, t_vec4 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w);
}

t_vec	vec4_to_vec(t_vec4 v)
{
	return ((t_vec){v.x, v.y, v.z});
}

t_vec4	vec_to_vec4(t_vec v)
{
	return ((t_vec4){v.x, v.y, v.z, 1});
}

t_vec4	arr_to_vec4(double arr[4])
{
	return ((t_vec4){arr[0], arr[1], arr[2], arr[3]});
}
