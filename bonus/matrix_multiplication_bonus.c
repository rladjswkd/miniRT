/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_multiplication_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 19:56:31 by gyepark           #+#    #+#             */
/*   Updated: 2022/11/11 19:56:31 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structure_bonus.h"
#include "vec4_operations_bonus.h"

t_vec4	mat_mul_vec4(t_mat mat, t_vec4 v)
{
	return ((t_vec4){vec4_dot(arr_to_vec4(mat.arr[0]), v),
		vec4_dot(arr_to_vec4(mat.arr[1]), v),
		vec4_dot(arr_to_vec4(mat.arr[2]), v),
		vec4_dot(arr_to_vec4(mat.arr[3]), v)});
}

t_mat	mat_mul(t_mat mat1, t_mat mat2)
{
	t_mat	ret;
	int		i;
	int		j;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			ret.arr[i][j] = vec4_dot(arr_to_vec4(mat1.arr[i]),
					(t_vec4){mat2.arr[0][j], mat2.arr[1][j],
					mat2.arr[2][j], mat2.arr[3][j]});
	}
	ret.len = 4;
	return (ret);
}
