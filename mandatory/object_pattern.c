/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_pattern.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 19:56:45 by gyepark           #+#    #+#             */
/*   Updated: 2022/11/11 19:56:46 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structure.h"
#include "vector_operation.h"
#include <math.h>

t_vec	get_basis_vec(t_vec v)
{
	t_vec	bx;
	t_vec	by;
	t_vec	bz;

	bx = (t_vec){1, 0, 0};
	by = (t_vec){0, 1, 0};
	bz = (t_vec){0, 0, 1};
	if (fabs(vec_dot(v, bx)) < 1e-6)
		return (bx);
	else if (fabs(vec_dot(v, bz)) < 1e-6)
		return (bz);
	return (by);
}
