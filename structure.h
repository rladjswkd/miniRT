/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 19:59:56 by gyepark           #+#    #+#             */
/*   Updated: 2022/11/11 20:02:53 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_H
# define STRUCTURE_H

typedef struct s_img
{
	void	*ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_obj
{
	int		type;
	void	*object;
	double	t;
}	t_obj;

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

typedef struct s_coordinate
{
	double	x;
	double	y;
	double	z;
}	t_coord;

typedef t_coord	t_vec;

typedef struct s_obj_info
{
	t_coord	coord;
	t_vec	norm;
	int		lati;
	int		longi;
	t_vec	norm_const;
}	t_obj_info;

typedef struct s_ambient
{
	double	intensity;
	t_rgb	rgb;
}	t_ambient;

typedef struct s_light
{
	t_coord	coord;
	double	intensity;
	t_rgb	rgb;
}	t_light;

typedef struct s_camera
{
	t_coord	coord;
	t_vec	norm;
	int		lati;
	int		longi;
	t_vec	norm_const;
	int		fov;
}	t_camera;

typedef struct s_sphere
{
	t_coord	coord;
	double	diameter;
	t_rgb	rgb;
}	t_sp;

typedef struct s_plane
{
	t_coord	coord;
	t_vec	norm;
	int		lati;
	int		longi;
	t_vec	norm_const;
	t_rgb	rgb;
}	t_pl;

typedef struct s_cylinder
{
	t_coord	coord;
	t_vec	norm;
	int		lati;
	int		longi;
	t_vec	norm_const;
	double	diameter;
	double	height;
	t_rgb	rgb;
}	t_cy;

typedef t_cy	t_cn;

typedef struct s_node
{
	void			*data;
	struct s_node	*next;
}	t_node;

typedef struct s_world
{
	t_ambient	a;
	t_camera	c;
	t_light		l;
	t_node		*sp;
	t_node		*cy;
	t_node		*pl;
}	t_world;

typedef struct s_ray
{
	t_vec	pos;
	t_vec	dir;
}	t_ray;

typedef struct s_intersection
{
	double	l;
	double	r;
}	t_inter;

typedef struct s_equation
{
	double	a;
	double	b;
	double	c;
}	t_equation;

typedef struct s_vec4
{
	double	x;
	double	y;
	double	z;
	double	w;
}	t_vec4;

typedef struct s_mat
{
	double	arr[4][4];
	int		len;
}	t_mat;

typedef struct s_viewport
{
	t_coord	top_left;
	t_vec	v_width;
	t_vec	v_height;
}	t_viewport;

typedef struct s_vars
{
	void		*mlx;
	void		*win;
	t_img		img;
	t_obj		obj;
}	t_vars;

typedef struct s_thread_param
{
	t_vars		*vars;
	t_world		*world;
	t_viewport	viewport;
}	t_thread_param;

typedef struct s_uv
{
	double	u;
	double	v;
	t_vec	pu;
	t_vec	pv;
}	t_uv;

#endif
