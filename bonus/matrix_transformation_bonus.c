/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_transformation_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 19:56:35 by gyepark           #+#    #+#             */
/*   Updated: 2022/11/11 19:56:36 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structure_bonus.h"
#include "matrix_rotation_bonus.h"
#include <math.h>

t_mat	get_rx_to_z(t_vec forward)
{
	double	len_yz_proj;
	double	cosine;
	double	sine;
	t_mat	mat_arr[4];

	len_yz_proj = sqrt(pow(forward.y, 2) + pow(forward.z, 2));
	if (len_yz_proj < 1e-6)
		return (mat_rx(cos(M_PI / 2), forward.x * sin(M_PI / 2)));
	cosine = fabs(forward.z) / len_yz_proj;
	sine = fabs(forward.y) / len_yz_proj;
	mat_arr[0] = mat_rx(cosine, sine);
	mat_arr[1] = mat_rx(cosine, -sine);
	mat_arr[3] = mat_arr[1];
	mat_arr[2] = mat_arr[0];
	return (mat_arr[(fabs(forward.y) > 1e-6 && forward.y < 0)
			+ 2 * (fabs(forward.z) > 1e-6 && forward.z < 0)]);
}

t_mat	get_ry_to_z(t_vec forward)
{
	double	cosine;
	double	sine;
	t_mat	mat_arr[4];

	cosine = fabs(forward.z);
	sine = fabs(forward.x);
	mat_arr[0] = mat_ry(cosine, -sine);
	mat_arr[1] = mat_ry(cosine, sine);
	mat_arr[3] = mat_arr[1];
	mat_arr[2] = mat_arr[0];
	return (mat_arr[(fabs(forward.x) > 1e-6 && forward.x < 0)
			+ 2 * (fabs(forward.z) > 1e-6 && forward.z < 0)]);
}

t_mat	mat_translation(double dx, double dy, double dz)
{
	return ((t_mat){{
			{1, 0, 0, dx},
			{0, 1, 0, dy},
			{0, 0, 1, dz},
			{0, 0, 0, 1}}, 4});
}

t_mat	rotate_latitude(int angle)
{
	double	rad;

	rad = angle * M_PI / 180;
	return (mat_rx(cos(rad), sin(rad)));
}

t_mat	rotate_longitude(int angle)
{
	double	rad;

	rad = angle * M_PI / 180;
	return (mat_ry(cos(rad), sin(rad)));
}
