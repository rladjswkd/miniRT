#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"
#include "string_utils.h"
#include "parser_util_split.h"
#include <math.h>
#include "converter.h"
#include "checker.h"

#define SPHERE		1
#define	CYLINDER	2
#define	PLANE		3
//#define	INFINITY	1e500
/*
removed
- t_circle structure
- intersect_circle function
- ray_pos function
- intersect_body function
- intersect_caps function
- get_min_intersection function

updated
- intersect_sphere (intersect_circle is merged here.)
- intersect_cylinder, cal_cy_body, cal_cy_caps (new algorithm.)
- t_intersection sturcture members' name

added
- t_equation structure
- solve_equation function
- choose_smaller_t function
- is_valid_t1, is_valid_t2, is_valid_t3, is_valid_t4 functions

*/
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

typedef	t_coord	t_vec;

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
	t_rgb	rgb;
}	t_pl;

typedef struct s_cylinder
{
	t_coord	coord;
	t_vec	norm;
	double	diameter;
	double	height;
	t_rgb	rgb;
}	t_cy;

typedef struct s_node
{
	void			*data;
	struct s_node	*next;
}	t_node;

typedef struct s_rt_info
{
	t_ambient	a;
	t_camera	c;
	t_light		l;
	t_node		*sp;
	t_node		*cy;
	t_node		*pl;
}	t_rt_info;

typedef struct s_object
{
	int		type;
	void	*object;
	double	t;
}	t_obj;

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

// typedef struct s_circle
// {
// 	t_coord	center;
// 	double	radius;
// }	t_circle;

typedef struct s_equation
{
	double	a;
	double	b;
	double	c;
}	t_equation;


int	check_rgb(t_rgb rgb)
{
	int	r;
	int	g;
	int	b;

	r = rgb.r;
	g = rgb.g;
	b = rgb.b;
	return (-1 < r && r < 256 && -1 < g && g < 256 && -1 < b && b < 256);
}

int	check_normal(t_vec vec)
{
	double	x;
	double	y;
	double	z;

	x = vec.x;
	y = vec.y;
	z = vec.z;
	return (-1 <= x && x <= 1 && -1 <= y && y <= 1 && -1 <= z && z <= 1
		&& sqrt(x * x + y * y + z * z) == 1);
}

int	free_splitted(char **splitted, int ret)
{
	int	i;

	i = -1;
	while (splitted[++i])
		free(splitted[i]);
	free(splitted);
	return (ret);
}

int	set_rgb(char *rgb_str, t_rgb *rgb)
{
	char	**rgb_info;
	int		rgb_info_cnt;

	if (!check_comma_cnt(rgb_str))
		return (0);
	rgb_info = split_line(rgb_str, ',', &rgb_info_cnt);
	if (rgb_info_cnt != 3
		|| !get_int(rgb_info[0], &(rgb->r))
		|| !get_int(rgb_info[1], &(rgb->g))
		|| !get_int(rgb_info[2], &(rgb->b)))
		return (free_splitted(rgb_info, 0));
	if (!check_rgb(*rgb))
		return (free_splitted(rgb_info, 0));
	return (free_splitted(rgb_info, 1));
}

int	set_coordinate(char *coord_str, t_coord *coord)
{
	char	**coord_info;
	int		coord_info_cnt;

	if (!check_comma_cnt(coord_str))
		return (0);
	coord_info = split_line(coord_str, ',', &coord_info_cnt);
	if (coord_info_cnt != 3
		|| !get_double(coord_info[0], &(coord->x))
		|| !get_double(coord_info[1], &(coord->y))
		|| !get_double(coord_info[2], &(coord->z)))
		return (free_splitted(coord_info, 0));
	return (free_splitted(coord_info, 1));
}

int	set_ambient(char **info, int cnt, t_rt_info *rt_info)
{
	double		intensity;
	t_ambient	*a;

	if (cnt != 3)
		return (0);
	a = &(rt_info->a);
	if (!get_double(info[1], &intensity) || intensity < 0 || 1 < intensity)
		return (0);
	if (!set_rgb(info[2], &(a->rgb)))
		return (0);
	a->intensity = intensity;
	return (1);
}

int	set_light(char **info, int cnt, t_rt_info *rt_info)
{
	double	intensitiy;
	t_light	*l;

	if (cnt != 4)
		return (0);
	l = &(rt_info->l);
	if (!set_coordinate(info[1], &(l->coord)))
		return (0);
	if (!get_double(info[2], &intensitiy) || intensitiy < 0 || 1 < intensitiy)
		return (0);
	if (!set_rgb(info[3], &(l->rgb)))
		return (0);
	l->intensity = intensitiy;
	return (1);
}

int	set_camera(char **info, int cnt, t_rt_info *rt_info)
{
	int			fov;
	t_camera	*c;

	if (cnt != 4)
		return (0);
	c = &(rt_info->c);
	if (!set_coordinate(info[1], &(c->coord)))
		return (0);
	if (!set_coordinate(info[2], &(c->norm))
		|| !check_normal(c->norm))
		return (0);
	if (!get_int(info[3], &fov)	|| fov < 0 || 180 < fov) // 180 0
		return (0);
	c->fov = fov;
	return (1);
}

t_node	*get_last_node(t_node *list) // this function is called after malloc, so list is non-null.
{
	while (list->next)
		list = list->next;
	return (list);
}

int	set_plane(char **info, int cnt, t_rt_info *rt_info)
{
	t_pl	*pl;

	if (cnt != 4)
		return (0);
	pl = (t_pl *)(get_last_node(rt_info->pl)->data);
	if (!set_coordinate(info[1], &(pl->coord)))
		return (0);
	if (!set_coordinate(info[2], &(pl->norm))
		|| !check_normal(pl->norm))
		return (0);
	if (!set_rgb(info[3], &(pl->rgb)))
		return (0);
	return (1);
}

int	set_sphere(char **info, int cnt, t_rt_info *rt_info)
{
	double	diameter;
	t_sp	*sp;

	if (cnt != 4)
		return (0);
	sp = (t_sp *)(get_last_node(rt_info->sp)->data);
	if (!set_coordinate(info[1], &(sp->coord)))
		return (0);
	if (!get_double(info[2], &diameter) || diameter < 0)
		return (0);
	if (!set_rgb(info[3], &(sp->rgb)))
		return (0);
	sp->diameter = diameter;
	return (1);
}

int	set_cylinder(char **info, int cnt, t_rt_info *rt_info)
{
	double	diameter;
	double	height;
	t_cy	*cy;

	if (cnt != 6)
		return (0);
	cy = (t_cy *)(get_last_node(rt_info->cy)->data);
	if (!set_coordinate(info[1], &(cy->coord)))
		return (0);
	if (!set_coordinate(info[2], &(cy->norm))
		|| !check_normal(cy->norm))
		return (0);
	if (!get_double(info[3], &diameter) || diameter < 0)
		return (0);
	if (!get_double(info[4], &height) || height < 0)
		return (0);
	if (!set_rgb(info[5], &(cy->rgb)))
	cy->diameter = diameter;
	cy->height = height;
	return (1);
}

int	alloc_sphere(void **ptr){
	t_sp	*sp;
	
	sp = (t_sp *)malloc(sizeof(t_sp));
	if (!sp)
		return (0);
	*ptr = (void *)sp;
	return (1);
}

int	alloc_plane(void **ptr){
	t_pl	*pl;
	
	pl = (t_pl *)malloc(sizeof(t_pl));
	if (!pl)
		return (0);
	*ptr = (void *)pl;
	return (1);
}

int	alloc_cylinder(void **ptr){
	t_cy	*cy;
	
	cy = (t_cy *)malloc(sizeof(t_cy));
	if (!cy)
		return (0);
	*ptr = (void *)cy;
	return (1);
}

int	alloc_new_node(t_node **node, int index)
{
	static int	(*allocator[3])(void **)
		= {alloc_sphere, alloc_plane, alloc_cylinder};
	
	*node = (t_node *)malloc(sizeof(t_node));
	if (!(*node))
		return (0);
	(*node)->next = 0;
	if (!(*allocator[index - 3])(&((*node)->data)))
	{
		free(*node);
		return (0);
	}
	return (1);
}

void	append_node(t_node **lst, t_node *new)
{
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	while ((*lst)->next)
		lst = &((*lst)->next);
	(*lst)->next = new;
}

void	clear_list(t_node **lst) // will be used in error handling function right before exit().
{
	t_node	*next;

	while (*lst)
	{
		next = (*lst)->next;
		free((*lst)->data);
		free(*lst);
		*lst = next;
	}
	*lst = 0;
}

int	set_object_list(t_rt_info *rt, int index)
{
	t_node	**objects;
	t_node	*new_node;

	if (!alloc_new_node(&new_node, index))
		return (0);
	objects = &(rt->sp);
	if (index == 4)
		objects = &(rt->pl);
	else if (index == 5)
		objects = &(rt->cy);
	append_node(objects, new_node);
	return (1);
}

/*
splitted
	1. 널 포인터 및 빈 문자열일 때 : 가드가 거름.
	2. 내용은 있지만, 유효하지 않은 상태일 때 : 각 set_* 함수들이 걸러야 함.
*/
int	set_rt_info(char *line, t_rt_info *rt, int *mask)
{
	char		**splitted;
	int			cnt;
	int			index;
	static int	(*fp[6])(char **, int, t_rt_info *) = {set_ambient, set_camera,
		set_light, set_sphere, set_plane, set_cylinder};
	
	splitted = split_line(line, ' ', &cnt); // all split_lines need null-guard.
	if (!(splitted && splitted[0]))
		return (free_splitted(splitted, 0));
	index = check_identifier(splitted[0]);
	if (index == -1)
		return (free_splitted(splitted, 0)); // caller must print error if set_rt_info returns 0.
	if (index < 3 && (*mask & 1 << index || !(*fp[index])(splitted, cnt, rt))) // A, C, L shouldn't be on mutiple lines and don't need malloc.
		return (free_splitted(splitted, 0));
	*mask |= 1 << index;
	if (2 < index
		&& (!set_object_list(rt, index)	|| !(*fp[index])(splitted, cnt, rt)))
		return (free_splitted(splitted, 0));
	return (free_splitted(splitted, 1));
}

t_vec	vec_add(t_vec v1, t_vec v2)
{
	return ((t_vec){v1.x + v2.x, v1.y + v2.y, v1.z + v2.z});
}

t_vec	vec_sub(t_vec v1, t_vec v2)
{
	return ((t_vec){v1.x - v2.x, v1.y - v2.y, v1.z - v2.z});
}

t_vec	vec_scale(t_vec vec, double scalar)
{
	return ((t_vec){vec.x * scalar, vec.y * scalar, vec.z * scalar});
}

double	vec_dot(t_vec v1, t_vec v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vec	vec_cross(t_vec v1, t_vec v2)
{
	return ((t_vec){v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z,
		v1.x * v2.y - v1.y * v2.x});
}

double	vec_len(t_vec vec)
{
	return (sqrt(vec_dot(vec, vec)));
}

t_vec	vec_normalize(t_vec vec)
{
	double	length;

	length = vec_len(vec);
	return ((t_vec){vec.x / length, vec.y / length, vec.z / length});
}

t_vec	vec_proj(t_vec v1, t_vec v2)
{
	double	scalar;

	scalar = vec_dot(v1, v2) / vec_len(v2);
	return ((t_vec){v2.x * scalar, v2.y * scalar, v2.z * scalar});
}

// int	get_min_intersection(double *ret, t_inter i)
// {
// 	if (i.l <= 1 && i.r <= 1)
// 		return (0);
// 	*ret = i.r;
// 	if (i.l > 1)
// 		*ret = i.l;
// 	return (1);
// }

double	choose_smaller_t(double current, double candidate, int condition)
{
	if (!condition || current < candidate)
		return (current);
	return (candidate);
}

// int	intersect_circle(t_ray ray, t_circle cir, t_inter *inter) // rename this to cal_sphere_t
// {
// 	double		a;
// 	double		b;
// 	double		c;
// 	double		discriminant;
// 	t_vec		ray_sp;

// 	ray_sp = vec_sub(ray.pos, cir.center);
// 	a = vec_dot(ray.dir, ray.dir);
// 	b = 2 * vec_dot(ray_sp, ray.dir);
// 	c = vec_dot(ray_sp, ray_sp) - pow(cir.radius, 2);
// 	discriminant = b * b - 4 * a * c;
// 	if (discriminant < 0)
// 		return (0);
// 	inter->l = (-b - sqrt(discriminant)) / (2 * a); // smaller
// 	inter->r = (-b + sqrt(discriminant)) / (2 * a); // bigger
// 	return (1);
// }

// int	intersect_sphere(t_ray ray, t_sp sp, double *t)// rename this to get_sphere_t and remove t_circle things.
// {
// 	t_inter		*i;
// 	t_circle	p;

// 	p.center = sp.coord;
// 	p.radius = sp.diameter / 2;
// 	return (intersect_circle(ray, p, i) && get_min_intersection(t, *i));
// }

void	solve_equation(t_equation eq, t_inter *inter)
{
	double	d;

	d = eq.b * eq.b - 4 * eq.a * eq.c;
	if (!d)
	{
		inter->l = HUGE_VAL; // 
		inter->r = HUGE_VAL; // is it possible to use HUGE_VAL constant?
	}
	inter->l = (-eq.b - sqrt(d)) / (2 * eq.a);
	inter->r = (-eq.b + sqrt(d)) / (2 * eq.a); // it is not necessary to compare l and r here.
}

int	intersect_sphere(t_ray ray, t_sp sp, double *t)// rename this to get_sphere_t and remove t_circle things.
{
	t_inter		inter;
	t_equation	eq;
	t_vec		ray_sp;
	double		ret;

	ray_sp = vec_sub(ray.pos, sp.coord);
	eq.a = vec_dot(ray.dir, ray.dir);
	eq.b = 2 * vec_dot(ray_sp, ray.dir);
	eq.c = vec_dot(ray_sp, ray_sp) - pow(sp.diameter / 2, 2);
	solve_equation(eq, &inter);
	ret = choose_smaller_t(HUGE_VAL, inter.l, (1 < inter.l));
	ret = choose_smaller_t(*t, inter.r, (1 < inter.r));
	*t = ret;
	return (ret != HUGE_VAL);
}

void	cal_cy_body(t_ray ray, t_cy cy, t_inter *inter)
{
	t_equation	eq;
	t_vec		vec_dir;
	t_vec		vec_pos;
	t_vec		cy_ray;

	vec_dir = vec_sub(ray.dir, vec_scale(cy.norm, vec_dot(ray.dir, cy.norm)));
	cy_ray = vec_sub(ray.pos, cy.coord);
	vec_pos = vec_sub(cy_ray, vec_scale(cy.norm, vec_dot(cy_ray, cy.norm)));
	eq.a = vec_dot(vec_dir, vec_dir);
	eq.b = 2 * vec_dot(vec_dir, vec_pos);
	eq.c = vec_dot(vec_pos, vec_pos) - pow(cy.diameter / 2, 2);
	solve_equation(eq, inter);
}

void	cal_cy_caps(t_ray ray, t_cy cy, t_inter *inter)
{
	t_vec	bottom_center;
	t_vec	top_center;
	double	n_dot_dir;

	bottom_center = cy.coord;
	top_center = vec_add(cy.coord, vec_scale(cy.norm, cy.height));
	n_dot_dir = vec_dot(cy.norm, ray.dir);
	inter->l = vec_dot(cy.norm, vec_sub(ray.pos, bottom_center)) / n_dot_dir;
	inter->r = vec_dot(cy.norm, vec_sub(ray.pos, top_center)) / n_dot_dir;
}
int	is_valid_t1(t_cy cy, t_ray ray, double t)
{
	return (t >= 0 && vec_dot(cy.norm, vec_sub(
		vec_add(ray.pos, vec_scale(ray.dir, t)), cy.coord)) > 0);
}

int	is_valid_t2(t_cy cy, t_ray ray, double t)
{
	return (t >= 0 && vec_dot(cy.norm, vec_sub(
		vec_add(ray.pos, vec_scale(ray.dir, t)),
		vec_add(cy.coord, vec_scale(cy.norm, cy.height)))) > 0);
}

int	is_valid_t3(t_cy cy, t_ray ray, double t)
{
	t_vec	q_to_cap;

	q_to_cap = vec_sub(vec_add(ray.pos, vec_scale(ray.dir, t)),
		cy.coord);
	return (t >= 0 && vec_dot(q_to_cap, q_to_cap) < pow(cy.diameter / 2, 2));
}

int	is_valid_t4(t_cy cy, t_ray ray, double t)
{
	t_vec	q_to_cap;

	q_to_cap = vec_sub(vec_add(ray.pos, vec_scale(ray.dir, t)),
		vec_add(cy.coord, vec_scale(cy.norm, cy.height)));
	return (t >= 0 && vec_dot(q_to_cap, q_to_cap) < pow(cy.diameter / 2, 2));
}
// t1 : nonnegative, vec_dot(cy.norm, vec_sub(q, p1)) > 0
// t2 : nonnegative, vec_dot(cy.norm, vec_sub(q, p2)) < 0
// t3 : nonnegative, vec_dot(vec_sub(q, p1), vec_sub(q, p1)) < r^2
// t4 : nonnegative, vec_dot(vec_sub(q, p2), vec_sub(q, p2)) < r^2
int	intersect_cylinder(t_ray ray, t_cy cy, double *t)// rename this to get_cylinder_t
{
	t_inter		t_1_2;
	t_inter		t_3_4;
	double		ret;

	cal_cy_body(ray, cy, &t_1_2);
	cal_cy_body(ray, cy, &t_3_4);
	ret = choose_smaller_t(HUGE_VAL, t_1_2.l, is_valid_t1(cy, ray, t_1_2.l));
	ret = choose_smaller_t(ret, t_1_2.r, is_valid_t2(cy, ray, t_1_2.r));
	ret = choose_smaller_t(ret, t_3_4.l, is_valid_t3(cy, ray, t_3_4.l));
	ret = choose_smaller_t(ret, t_3_4.r, is_valid_t4(cy, ray, t_3_4.r));
	*t = ret;
	return (ret != HUGE_VAL);
}

// t_vec	ray_pos(t_ray ray, double t)
// {
// 	return (vec_add(ray.pos, vec_scale(ray.dir, t)));
// }

// int	intersect_cylinder(t_ray ray, t_cy cy, double *t) // ray랑 normal이랑 평행한 지 확인해야 한다., get_min_intersection을 체크하는 함수 포인터를 전달한다.
// {
// 	t_inter	inter1;
// 	t_inter	inter2;
// 	double	l;
// 	double	r;

// 	if (fabs(vec_len(vec_proj(vec_normalize(ray.dir), cy.norm)) - 1) < 1e-6)
// 	{
// 		if (!intersect_caps(ray, cy, &inter2)
// 			|| !get_min_intersection(&r, inter2))
// 			return (0);
// 		*t = r;
// 		return (1);
// 	}
// 	if (!intersect_body(ray, cy, &inter1))
// 		return (0);
// 	get_min_intersection(&l, inter1);
// 	inter2.l = 0;
// 	inter2.r = 0;
// 	intersect_caps(ray, cy, &inter2);
// 	get_min_intersection(&r, inter2);
// 	if (!get_min_intersection(&t, (t_inter){l, r}))
// 		return (0);
// 	return (1);		
// }
// // unit vector check
// // cylinder is infinite.
// int	intersect_body(t_ray ray, t_cy cy, t_inter *inter)
// {
// 	t_vec		c_perp;
// 	t_ray		r_perp;
// 	double		proj_t1;
// 	double		proj_t2;

// 	c_perp = vec_sub(cy.coord, vec_proj(cy.coord, cy.norm));
// 	r_perp.pos = vec_sub(ray.pos, vec_proj(ray.pos, cy.norm));
// 	r_perp.dir = vec_sub(ray.dir, vec_proj(ray.dir, cy.norm));
// 	if (!intersect_circle(r_perp, (t_circle){c_perp, cy.diameter / 2}, inter))
// 		return (0);
// 	proj_t1 = vec_len(vec_proj(vec_sub(ray_pos(ray, inter->l), cy.coord), cy.norm));
// 	proj_t2 = vec_len(vec_proj(vec_sub(ray_pos(ray, inter->r), cy.coord), cy.norm));
// 	if (proj_t1 < 0 || cy.height < proj_t1)
// 		inter->l = -1;
// 	if (proj_t2 < 0 || cy.height < proj_t2)
// 		inter->r = -1;
// 	return (1);
// }

// int	intersect_caps(t_ray ray, t_cy cy, t_inter *inter)
// {
// 	double	bottom;
// 	double	top;
// 	double	c_to_t1;
// 	double	c_to_t2;
// 	double	radius;

// 	bottom = vec_len(vec_proj(cy.coord, cy.norm));
// 	top = bottom + cy.height;
// 	inter->l = (bottom - vec_len(vec_proj(ray.pos, cy.norm)))
// 		/ vec_len(vec_proj(ray.dir, cy.norm));
// 	inter->r = (top - vec_len(vec_proj(ray.pos, cy.norm)))
// 		/ vec_len(vec_proj(ray.dir, cy.norm));
// 	c_to_t1 = vec_len(vec_sub(ray_pos(ray, inter->l), cy.coord));
// 	c_to_t2 = vec_len(vec_sub(ray_pos(ray, inter->r), vec_add(
// 			cy.coord, vec_scale(cy.norm, cy.height))));
// 	radius = cy.diameter / 2;
// 	if (c_to_t1 >= radius && c_to_t2 >= radius)
// 		return (0);
// 	if (c_to_t1 >= radius)
// 		inter->l = -1;
// 	if (c_to_t2 >= radius)
// 		inter->r = -1;
// 	return (1);
// }

int	intersect_plane(t_ray ray, t_pl pl, double *t) //rename this to get_plane_t
{
	double	ray_pl_dot;

	ray_pl_dot = vec_dot(ray.pos, pl.norm);
	if (ray_pl_dot < 1e-6)
		return (0);
	*t = vec_dot(vec_sub(pl.coord, ray.pos), pl.norm) / ray_pl_dot;
	return (1);
}

void	check_sp(t_ray ray, t_node *sp, t_obj *obj, double initial)
{
	double	cur;
	double	t;

	if (!sp)
		return ;
	t = initial;
	while (sp->data)
	{
		if (intersect_sphere(ray, *((t_sp *)(sp->data)), &cur) && cur < t)
		{
			t = cur;
			obj->type = SPHERE;
			obj->object = (t_sp *)(sp->data);
		}
	}
	obj->t = t;
}

void	check_cy(t_ray ray, t_node *cy, t_obj *obj, double initial)
{
	double	cur;
	double	t;

	if (!cy)
		return ;
	t = initial;
	while (cy->data)
	{
		if (intersect_cylinder(ray, *((t_cy *)(cy->data)), &cur) && cur < t)
		{
			t = cur;
			obj->type = CYLINDER;
			obj->object = (t_cy *)(cy->data);
		}
	}
	obj->t = t;
}

void	check_pl(t_ray ray, t_node *pl, t_obj *obj, double initial)
{
	double	cur;
	double	t;

	if (!pl)
		return ;
	t = initial;
	while (pl->data)
	{
		if (intersect_plane(ray, *((t_pl *)(pl->data)), &cur) && cur < t)
		{
			t = cur;
			obj->type = PLANE;
			obj->object = (t_pl *)(pl->data);
		}
	}
	obj->t = t;
}

int	intersect(t_ray ray, t_rt_info info, t_obj *obj)
{
	obj->type = 0;
	obj->t = INFINITY;
	check_sp(ray, info.sp, obj, obj->t);
	check_cy(ray, info.cy, obj, obj->t);
	check_pl(ray, info.pl, obj, obj->t);
    return (obj->type);
}

double	compute_lighting(t_vec p, t_vec n, t_rt_info info) // only for diffuse reflection, p_norm should be an unit vector
{
	double	lighting;
	t_vec	p_to_l;
	double	n_dot_l;

	lighting = info.a.intensity;
	p_to_l = vec_sub(info.l.coord, p);
	n_dot_l = vec_dot(n, p_to_l);
	if (n_dot_l > 0)
		lighting += info.l.intensity * n_dot_l / (vec_len(n) * vec_len(p_to_l));
	// shadow part should be added here
    return (lighting);
}

int	open_file(char *path)
{
	int	fd;
	int	len;

	fd = -1;
	len = ft_strlen(path);
	if (path[len - 3] == '.' && path[len - 2] == 'r' && path[len - 1] == 't')
		fd = open(path, O_RDONLY); // is read-only enough?
	// call error handling function to exit.
	return (fd);
}

int	read_file(int fd, t_rt_info *rt_info)
{
	char		*line;
	int			flag;
	static int	mask = 0; // bit-mask to check A, C, L should be declared only and at least once.

	flag = 1;
	while (flag)
	{
		line = get_next_line(fd);
		if (line == 0)
			break ;
		if (line[0] != '\0')
			flag = set_rt_info(line, rt_info, &mask);
		free(line);
	}
	if (!flag || !(mask & 1 << 0 && mask & 1 << 1 && mask & 1 << 2))
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	int			fd;
	t_rt_info	rt_info;

	if (argc != 2)
		return (0); // call error handling function with proper error message.
	fd = open_file(argv[1]);
	if (fd < 0) // remove this when error handling function is completed.
		return (0); // 에러 문자열 출력하고 처리해주기
	rt_info.sp = 0;
	rt_info.pl = 0;
	rt_info.cy = 0;
	if (read_file(fd, &rt_info))
		printf("%s\n", "valid format");
	else
		printf("%s\n", "invalid format");
	/* draw image */
	clear_list(&(rt_info.sp));
	clear_list(&(rt_info.pl));
	clear_list(&(rt_info.cy));
	return (0);
}