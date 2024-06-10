/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_rotation_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 19:56:33 by gyepark           #+#    #+#             */
/*   Updated: 2022/11/11 19:56:34 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structure_bonus.h"
#include <math.h>

t_mat	mat_rx(double cosine, double sine)
{
	cosine = cosine * (fabs(cosine) > 1e-6);
	sine = sine * (fabs(sine) > 1e-6);
	return ((t_mat){{
			{1, 0, 0, 0},
			{0, cosine, -sine, 0},
			{0, sine, cosine, 0},
			{0, 0, 0, 1}}, 4});
}

t_mat	mat_ry(double cosine, double sine)
{
	cosine = cosine * (fabs(cosine) > 1e-6);
	sine = sine * (fabs(sine) > 1e-6);
	return ((t_mat){{
			{cosine, 0, sine, 0},
			{0, 1, 0, 0},
			{-sine, 0, cosine, 0},
			{0, 0, 0, 1}}, 4});
}

t_mat	mat_rz(double cosine, double sine)
{
	cosine = cosine * (fabs(cosine) > 1e-6);
	sine = sine * (fabs(sine) > 1e-6);
	return ((t_mat){{
			{cosine, -sine, 0, 0},
			{sine, cosine, 0, 0},
			{0, 0, 1, 0},
			{0, 0, 0, 1}}, 4});
}
