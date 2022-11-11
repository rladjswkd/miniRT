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

char	uv_pattern_at(t_uv uv, int w, int h)
{
	if (((int)floor(uv.u * w) + (int)floor(uv.v * h)) % 2)
		return (1);
	return (0);
}

t_rgb	get_img_rgb(t_img img, t_uv uv)
{
	int	i;

	i = img.width * uv.u + ((int)(img.height * uv.v)) * img.width;
	i *= 4;
	return ((t_rgb){(unsigned char)img.addr[i + 2],
		(unsigned char)img.addr[i + 1], (unsigned char)img.addr[i]});
}

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
