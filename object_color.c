/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 19:56:43 by gyepark           #+#    #+#             */
/*   Updated: 2022/11/11 19:56:43 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structure.h"
#include "constant.h"
#include "uv_mapper.h"
#include "object_pattern.h"

static t_rgb	get_sp_rgb(t_img img, void *object, t_coord p)
{
	t_uv	uv;
	t_sp	*sp;

	sp = object;
	if ((sp->status & CHECKER))
	{
		uv = uv_map_sphere(p, *sp);
		if (uv_pattern_at(uv, 16, 16))
		{
			if (sp->status & IMAGE)
				return (get_img_rgb(img, uv));
			return (sp->rgb);
		}
		return ((t_rgb){255, 255, 255});
	}
	if (sp->status & IMAGE)
	{
		uv = uv_map_sphere(p, *sp);
		return (get_img_rgb(img, uv));
	}
	return (sp->rgb);
}

static t_rgb	get_pl_rgb(t_img img, void *object, t_coord p)
{
	t_uv	uv;
	t_pl	*pl;

	pl = object;
	if ((pl->status & CHECKER))
	{
		uv = uv_map_plane(p, *pl);
		if (uv_pattern_at(uv, 16, 16))
		{
			if (pl->status & IMAGE)
				return (get_img_rgb(img, uv));
			return (pl->rgb);
		}
		return ((t_rgb){255, 255, 255});
	}
	if (pl->status & IMAGE)
	{
		uv = uv_map_plane(p, *pl);
		return (get_img_rgb(img, uv));
	}
	return (pl->rgb);
}

static t_rgb	get_cy_rgb(t_img img, void *object, t_coord p)
{
	t_uv	uv;
	t_cy	*cy;

	cy = object;
	if ((cy->status & CHECKER))
	{
		uv = uv_map_cylinder(p, *cy);
		if (uv_pattern_at(uv, 16, 8))
		{
			if (cy->status & IMAGE)
				return (get_img_rgb(img, uv));
			return (cy->rgb);
		}
		return ((t_rgb){255, 255, 255});
	}
	if (cy->status & IMAGE)
	{
		uv = uv_map_cylinder(p, *cy);
		return (get_img_rgb(img, uv));
	}
	return (cy->rgb);
}

static t_rgb	get_cn_rgb(t_img img, void *object, t_coord p)
{
	t_uv	uv;
	t_cn	*cn;

	cn = object;
	if ((cn->status & CHECKER))
	{
		uv = uv_map_cone(p, *cn);
		if (uv_pattern_at(uv, 16, 16))
		{
			if (cn->status & IMAGE)
				return (get_img_rgb(img, uv));
			return (cn->rgb);
		}
		return ((t_rgb){255, 255, 255});
	}
	if (cn->status & IMAGE)
	{
		uv = uv_map_cone(p, *cn);
		return (get_img_rgb(img, uv));
	}
	return (cn->rgb);
}

t_rgb	get_obj_rgb(t_vars *vars, t_obj obj, t_coord p, t_vec lighting)
{
	t_rgb			ret;
	static t_rgb	(*fp[4])(t_img, void *, t_coord) = {
		get_sp_rgb, get_cy_rgb, get_pl_rgb, get_cn_rgb};

	ret = (*fp[obj.type - 1])(vars->c_img, obj.object, p);
	return ((t_rgb){
		(int)(lighting.x * ret.r),
		(int)(lighting.y * ret.g),
		(int)(lighting.z * ret.b)
	});
}
