/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_transformation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 19:56:41 by gyepark           #+#    #+#             */
/*   Updated: 2022/11/11 19:56:41 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structure.h"
#include "constant.h"
#include "matrix_transformation.h"
#include "vec4_operations.h"
#include "matrix_multiplication.h"
#include "matrix_transpose.h"
#include "vector_operation.h"

t_vec	rotate_normal(t_vec vec, t_mat op)
{
	t_mat	rx;
	t_mat	ry;
	t_vec4	res;

	rx = get_rx_to_z(vec);
	res = mat_mul_vec4(rx, vec_to_vec4(vec));
	ry = get_ry_to_z(vec4_to_vec(res));
	res = mat_mul_vec4(ry, res);
	res = mat_mul_vec4(op, res);
	res = mat_mul_vec4(mat_transpose(ry), res);
	res = mat_mul_vec4(mat_transpose(rx), res);
	return (vec4_to_vec(res));
}
