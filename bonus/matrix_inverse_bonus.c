/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_inverse_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 19:56:28 by gyepark           #+#    #+#             */
/*   Updated: 2022/11/11 19:56:28 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structure_bonus.h"
#include "matrix_transpose_bonus.h"

static t_mat	mat_submat(t_mat mat, int r, int c)
{
	t_mat	ret;
	int		ret_i;
	int		ret_j;
	int		i;
	int		j;

	i = -1;
	ret_i = -1;
	while (++i < mat.len)
	{
		if (i == r)
			continue ;
		++ret_i;
		j = -1;
		ret_j = -1;
		while (++j < mat.len)
		{
			if (j == c)
				continue ;
			ret.arr[ret_i][++ret_j] = mat.arr[i][j];
		}
	}
	ret.len = mat.len - 1;
	return (ret);
}

static double	mat_determinant(t_mat mat)
{
	double	det;
	int		i;

	det = 0;
	if (mat.len == 2)
		return (mat.arr[0][0] * mat.arr[1][1] - mat.arr[0][1] * mat.arr[1][0]);
	i = -1;
	while (++i < mat.len)
		det += mat.arr[0][i]
			* (1 - 2 * (i % 2)) * mat_determinant(mat_submat(mat, 0, i));
	return (det);
}

static t_mat	mat_comatrix(t_mat mat)
{
	t_mat	comatrix;
	int		i;
	int		j;
	int		len;

	len = mat.len;
	i = -1;
	while (++i < len)
	{
		j = -1;
		while (++j < len)
			comatrix.arr[i][j] = (1 - 2 * ((i + j) % 2))
				* mat_determinant(mat_submat(mat, i, j));
	}
	comatrix.len = len;
	return (comatrix);
}

static t_mat	mat_scale(t_mat mat, double scalar)
{
	t_mat	ret;
	int		i;
	int		j;
	int		len;

	len = mat.len;
	i = -1;
	while (++i < len)
	{
		j = -1;
		while (++j < len)
			ret.arr[i][j] = mat.arr[i][j] / scalar;
	}
	ret.len = len;
	return (ret);
}

t_mat	mat_inverse(t_mat mat)
{
	return (mat_scale(mat_transpose(mat_comatrix(mat)), mat_determinant(mat)));
}
