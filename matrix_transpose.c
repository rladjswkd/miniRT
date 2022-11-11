/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_transpose.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 19:56:38 by gyepark           #+#    #+#             */
/*   Updated: 2022/11/11 19:56:39 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structure.h"

t_mat	mat_transpose(t_mat	mat)
{
	return ((t_mat){{
			{mat.arr[0][0], mat.arr[1][0], mat.arr[2][0], mat.arr[3][0]},
			{mat.arr[0][1], mat.arr[1][1], mat.arr[2][1], mat.arr[3][1]},
			{mat.arr[0][2], mat.arr[1][2], mat.arr[2][2], mat.arr[3][2]},
			{mat.arr[0][3], mat.arr[1][3], mat.arr[2][3], mat.arr[3][3]}
		}, mat.len});
}
