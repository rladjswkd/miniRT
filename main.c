#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"
#include "string_utils.h"
#include "parser_util_split.h"
#include <math.h>
#include "converter.h"
#include "checker.h"
#include "mlx.h"

#define SPHERE		1
#define	CYLINDER	2
#define	PLANE		3
#define ESC_KEY		53
#define LEFT			123
#define UP				126
#define RIGHT			124
#define DOWN			125
#define P_WID 1280
#define P_HEI 720

//#define	INFINITY	1e500
#define	S_EXP		10 // specular exponent

typedef struct s_img
{
	void	*ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_vars
{
	void		*mlx;
	void		*win;
	t_img		img;
}	t_vars;

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

typedef struct s_world
{
	t_ambient	a;
	t_camera	c;
	t_node		*l;
	t_node		*sp;
	t_node		*cy;
	t_node		*pl;
}	t_world;

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

int	init_mlx_pointers(t_vars *vars)
{
	vars->mlx = mlx_init();
	if (!vars->mlx)
		return (0);
	vars->win = mlx_new_window(vars->mlx, P_WID, P_HEI, "miniRT");
	if (!vars->win)
		return (0);
	vars->img.ptr = mlx_new_image(vars->mlx, P_WID, P_HEI);
	if (!vars->img.ptr)
		return (0);
	vars->img.addr = mlx_get_data_addr(vars->img.ptr, &vars->img.bits_per_pixel,
			&vars->img.line_length, &vars->img.endian);
	if (!vars->img.addr)
		return (0);
	return (1);
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

t_node	*get_last_node(t_node *list) // this function is called after malloc, so list is non-null.
{
	while (list->next)
		list = list->next;
	return (list);
}

int	set_ambient(char **info, int cnt, t_world *world)
{
	double		intensity;
	t_ambient	*a;

	if (cnt != 3)
		return (0);
	a = &(world->a);
	if (!get_double(info[1], &intensity) || intensity < 0 || 1 < intensity)
		return (0);
	if (!set_rgb(info[2], &(a->rgb)))
		return (0);
	a->intensity = intensity;
	return (1);
}

int	set_light(char **info, int cnt, t_world *world)
{
	double	intensitiy;
	t_light	*l;

	if (cnt != 4)
		return (0);
	l = (t_light *)(get_last_node(world->l)->data);
	if (!set_coordinate(info[1], &(l->coord)))
		return (0);
	if (!get_double(info[2], &intensitiy) || intensitiy < 0 || 1 < intensitiy)
		return (0);
	if (!set_rgb(info[3], &(l->rgb)))
		return (0);
	l->intensity = intensitiy;
	return (1);
}

int	set_camera(char **info, int cnt, t_world *world)
{
	int			fov;
	t_camera	*c;

	if (cnt != 4)
		return (0);
	c = &(world->c);
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


int	set_plane(char **info, int cnt, t_world *world)
{
	t_pl	*pl;

	if (cnt != 4)
		return (0);
	pl = (t_pl *)(get_last_node(world->pl)->data);
	if (!set_coordinate(info[1], &(pl->coord)))
		return (0);
	if (!set_coordinate(info[2], &(pl->norm))
		|| !check_normal(pl->norm))
		return (0);
	if (!set_rgb(info[3], &(pl->rgb)))
		return (0);
	return (1);
}

int	set_sphere(char **info, int cnt, t_world *world)
{
	double	diameter;
	t_sp	*sp;

	if (cnt != 4)
		return (0);
	sp = (t_sp *)(get_last_node(world->sp)->data);
	if (!set_coordinate(info[1], &(sp->coord)))
		return (0);
	if (!get_double(info[2], &diameter) || diameter < 0)
		return (0);
	if (!set_rgb(info[3], &(sp->rgb)))
		return (0);
	sp->diameter = diameter;
	return (1);
}

int	set_cylinder(char **info, int cnt, t_world *world)
{
	double	diameter;
	double	height;
	t_cy	*cy;

	if (cnt != 6)
		return (0);
	cy = (t_cy *)(get_last_node(world->cy)->data);
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
		return (0);
	cy->diameter = diameter;
	cy->height = height;
	return (1);
}

int	alloc_light(void **ptr){
	t_light	*l;

	l = (t_light *)malloc(sizeof(t_light));
	if (!l)
		return (0);
	*ptr = (void *)l;
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
	static int	(*allocator[4])(void **)
		= {alloc_light, alloc_sphere, alloc_plane, alloc_cylinder};
	
	*node = (t_node *)malloc(sizeof(t_node));
	if (!(*node))
		return (0);
	(*node)->next = 0;
	if (!(*allocator[index - 2])(&((*node)->data)))
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

int	set_object_list(t_world *rt, int index)
{
	t_node	**objects;
	t_node	*new_node;

	if (!alloc_new_node(&new_node, index))
		return (0);
	objects = &(rt->l);
	if (index == 3)
		objects = &(rt->sp);
	else if (index == 4)
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
int	set_world(char *line, t_world *rt, int *mask)
{
	char		**splitted;
	int			cnt;
	int			index;
	static int	(*fp[6])(char **, int, t_world *) = {set_ambient, set_camera,
		set_light, set_sphere, set_plane, set_cylinder};
	
	splitted = split_line(line, ' ', &cnt); // all split_lines need null-guard.
	if (!(splitted && splitted[0]))
		return (free_splitted(splitted, 0));
	index = check_identifier(splitted[0]);
	if (index == -1)
		return (free_splitted(splitted, 0)); // caller must print error if set_world returns 0.
	if (index < 2 && (*mask & 1 << index || !(*fp[index])(splitted, cnt, rt))) // A, C, L shouldn't be on mutiple lines and don't need malloc.
		return (free_splitted(splitted, 0));
	*mask |= 1 << index;
	if (1 < index
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
	t_vec	n;

	n = vec_normalize(v2);
	scalar = vec_dot(v1, v2);
	return ((t_vec){n.x * scalar, n.y * scalar, n.z * scalar});
}

t_vec	vec_neg(t_vec vec)
{
	return ((t_vec){-vec.x, -vec.y, -vec.z});
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
	if (condition && candidate < current)
		return (candidate);
	return (current);
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
	if (d < 0)
	{
		inter->l = HUGE_VAL; // 
		inter->r = HUGE_VAL; // is it possible to use HUGE_VAL constant?
		return ;
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
	ret = choose_smaller_t(ret, inter.r, (1 < inter.r));
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
	inter->l = vec_dot(cy.norm, vec_sub(bottom_center, ray.pos)) / n_dot_dir;
	inter->r = vec_dot(cy.norm, vec_sub(top_center, ray.pos)) / n_dot_dir;
}

int	is_valid_t1t2(t_cy cy, t_ray ray, double t)
{
	return (t > 1 && vec_dot(cy.norm, vec_sub(
		vec_add(ray.pos, vec_scale(ray.dir, t)), cy.coord)) > 0
		&& vec_dot(cy.norm, vec_sub( 
		vec_add(ray.pos, vec_scale(ray.dir, t)),
		vec_add(cy.coord, vec_scale(cy.norm, cy.height)))) < 0);
}

int	is_valid_t3(t_cy cy, t_ray ray, double t)
{
	t_vec	q_to_cap;

	q_to_cap = vec_sub(vec_add(ray.pos, vec_scale(ray.dir, t)),
		cy.coord);
	return (t > 1 && vec_dot(q_to_cap, q_to_cap) < pow(cy.diameter / 2, 2));
}

int	is_valid_t4(t_cy cy, t_ray ray, double t)
{
	t_vec	q_to_cap;

	q_to_cap = vec_sub(vec_add(ray.pos, vec_scale(ray.dir, t)),
		vec_add(cy.coord, vec_scale(cy.norm, cy.height)));
	return (t > 1 && vec_dot(q_to_cap, q_to_cap) < pow(cy.diameter / 2, 2));
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
	cal_cy_caps(ray, cy, &t_3_4);
	ret = choose_smaller_t(HUGE_VAL, t_1_2.l, is_valid_t1t2(cy, ray, t_1_2.l));
	ret = choose_smaller_t(ret, t_1_2.r, is_valid_t1t2(cy, ray, t_1_2.r));
	ret = choose_smaller_t(ret, t_3_4.l, is_valid_t3(cy, ray, t_3_4.l));
	ret = choose_smaller_t(ret, t_3_4.r, is_valid_t4(cy, ray, t_3_4.r));
	*t = ret;
	return (ret != HUGE_VAL);
}

int	intersect_plane(t_ray ray, t_pl pl, double *t) //rename this to get_plane_t
{
	double	ray_pl_dot;

	ray_pl_dot = vec_dot(ray.dir, pl.norm);
	if (ray_pl_dot < 1e-6)
		return (0);
	*t = vec_dot(vec_sub(pl.coord, ray.pos), pl.norm) / ray_pl_dot;
	return (*t > 1);
}

void	check_sp(t_ray ray, t_node *sp, t_obj *obj)
{
	double	cur;
	double	t;

	if (!sp)
		return ;
	t = obj->t;
	while (sp)
	{
		if (intersect_sphere(ray, *((t_sp *)(sp->data)), &cur) && cur < t)
		{
			t = cur;
			obj->type = SPHERE;
			obj->object = (t_sp *)(sp->data);
		}
		sp = sp->next;
	}
	obj->t = t;
}

void	check_cy(t_ray ray, t_node *cy, t_obj *obj)
{
	double	cur;
	double	t;

	if (!cy)
		return ;
	t = obj->t;
	while (cy)
	{
		if (intersect_cylinder(ray, *((t_cy *)(cy->data)), &cur) && cur < t)
		{
			t = cur;
			obj->type = CYLINDER;
			obj->object = (t_cy *)(cy->data);
		}
		cy = cy->next;
	}
	obj->t = t;
}

void	check_pl(t_ray ray, t_node *pl, t_obj *obj)
{
	double	cur;
	double	t;

	if (!pl)
		return ;
	t = obj->t;
	while (pl)
	{
		if (intersect_plane(ray, *((t_pl *)(pl->data)), &cur) && cur < t)
		{
			t = cur;
			obj->type = PLANE;
			obj->object = (t_pl *)(pl->data);
		}
		pl = pl->next;
	}
	obj->t = t;
}

int	intersect(t_ray ray, t_world world, t_obj *obj)
{
	obj->type = 0;
	obj->t = INFINITY;

	check_sp(ray, world.sp, obj);
	check_cy(ray, world.cy, obj);
	check_pl(ray, world.pl, obj);
    return (obj->type);
}

t_vec	rgb_to_vec(t_rgb rgb)
{
	return ((t_vec){rgb.r / 255.0, rgb.g / 255.0, rgb.b / 255.0});
}

t_rgb	mult_rgb_vec(t_rgb rgb, t_vec vec)
{
	return ((t_rgb){(int)(vec.x * rgb.r),
		(int)(vec.y * rgb.g), (int)(vec.z * rgb.b)});
}

t_vec	compute_ambients(t_world world)
{
	t_vec	ret;
	t_vec	tmp;
	t_node	*l;

	ret = (t_vec){0, 0, 0};
	l = world.l;
	while (l)
	{
		tmp = vec_scale(rgb_to_vec(((t_light *)l->data)->rgb), world.a.intensity);
		ret = vec_add(ret, tmp);
		l = l->next;
	}
	return (ret);
}

t_vec	compute_diffuse(t_vec inter, t_vec n, t_light light)
{
	t_vec	ret;
	t_vec	l;
	double	n_dot_l;

	ret = (t_vec){0, 0, 0};
	l = vec_normalize(vec_sub(light.coord, inter));
	n_dot_l = vec_dot(n, l);
	if (n_dot_l > 0)
		ret = vec_scale(rgb_to_vec(light.rgb), light.intensity * n_dot_l);
	return (ret);
}

t_vec	compute_specular(t_vec inter, t_vec n, t_vec v, t_light light)
{
	t_vec	ret;
	t_vec	l;
	t_vec	r;
	double	r_dot_v;

	ret = (t_vec){0, 0, 0};
	l = vec_normalize(vec_sub(light.coord, inter));
	r = vec_sub(vec_neg(l), vec_scale(n, 2.0 * vec_dot(n, vec_neg(l))));
	r_dot_v = vec_dot(v, r);
	if (r_dot_v > 0)
		ret = vec_scale(rgb_to_vec(light.rgb),
			light.intensity * pow(r_dot_v, S_EXP));
    return (ret);
}


t_vec	compute_lighting(t_vec inter, t_vec n, t_vec v, t_world world) // only for diffuse reflection, p_norm should be an unit vector
{
	t_vec	v_ambient;
	t_vec	v_diffuse;
	t_vec	v_specular;
	t_vec	lighting;
	t_node	*l;

	l = world.l;
	v_diffuse = (t_vec){0, 0, 0};
	v_specular = (t_vec){0, 0, 0};
	v_ambient = compute_ambients(world);
	while (l)
	{
		// if (check_shadow);
		v_diffuse = vec_add(v_diffuse,compute_diffuse(inter, n , *((t_light *)(l->data))));
		v_specular = vec_add(v_specular, compute_specular(inter, n, v,*((t_light *)(l->data))));
		l = l->next;
	}
	lighting = vec_add(vec_add(v_ambient, v_diffuse), v_specular);
	lighting.x -= (lighting.x > 1.0) * (lighting.x - 1.0);
	lighting.y -= (lighting.y > 1.0) * (lighting.y - 1.0);
	lighting.z -= (lighting.z > 1.0) * (lighting.z - 1.0);
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

int	read_file(int fd, t_world *world)
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
			flag = set_world(line, world, &mask);
		free(line);
	}
	if (!flag || !(mask & 1 << 0 && mask & 1 << 1 && mask & 1 << 2))
		return (0);
	return (1);
}

int	check_shadow_sp(t_ray ray, t_node *sp)
{
	double	cur;

	cur = 2;
	if (!sp)
		return (0);
	while (sp)
	{
		if (intersect_sphere(ray, *((t_sp *)(sp->data)), &cur) && cur < 2)
			return (1);
		sp = sp->next;
	}
	return (0);
}

/////////////////////////////////////////////////////check_shadow
int	check_shadow_cy(t_ray ray, t_node *cy)
{
	double	cur;

	cur = 2;
	if (!cy)
		return (0);
	while (cy)
	{
		if (intersect_cylinder(ray, *((t_cy *)(cy->data)), &cur) && cur < 2)
			return (1);
		cy = cy->next;
	}
	return (0);
}

int	check_shadow_pl(t_ray ray, t_node *pl)
{
	double	cur;

	cur = 2;
	if (!pl)
		return (0);
	while (pl)
	{
		if (intersect_plane(ray, *((t_pl *)(pl->data)), &cur) && cur < 2)
			return (1);
		pl = pl->next;
	}
	return (0);
}

t_ray	get_l_ray(t_light l, t_ray ray, t_obj	obj)
{
	t_ray	l_ray;
	t_vec	t_pos;

	t_pos = vec_add(vec_scale(ray.dir, obj.t), ray.pos);
	l_ray.dir = vec_sub(l.coord, t_pos);
	l_ray.pos = vec_sub(t_pos, l_ray.dir);
	return (l_ray);
}

int	check_shadow(t_world world, t_ray l_ray)
{
	if (check_shadow_sp(l_ray, world.sp))
		return (1);
	if (check_shadow_cy(l_ray, world.cy))
		return (1);
	if (check_shadow_pl(l_ray, world.pl))
		return (1);
	return (0);
}

/////////////////////////////////////////////////////
typedef struct s_pixel_info
{
	t_coord	top_left;
	t_vec	p_h;
	t_vec	p_v;
}	t_p_info;
/////////////////////////////////////////////////////

t_vec	get_ab_vec(t_vec v)
{
	t_vec	ret;

	if (v.x == 0 && v.y == 0 && (v.z == 1 || v.z == -1))
	{
		ret.x = 1;
		ret.y = 0;
		ret.z = 0;
	}
	else
	{
		ret.x = 0;
		ret.y = 0;
		ret.z = 1;
	}
	return (ret);
}

void	get_pixel_info(t_camera c, t_p_info *p_info)
{
	t_vec	h;
	t_vec	v;
	t_vec	tmp;
	double	vp_h;
	double	vp_w;

	vp_w = tan((c.fov * M_PI / 180.0) / 2.0) * 2;
	vp_h = vp_w * ((double)P_HEI / (double)P_WID);
	h = vec_cross(c.norm, get_ab_vec(c.norm));
	v = vec_cross(c.norm, h);
	h = vec_scale(h, (double)1 / vec_len(h) * (vp_w / (double)P_WID));
	v = vec_scale(v, (double)1 / vec_len(v) * (vp_h / (double)P_HEI));
	p_info->p_h = h;
	p_info->p_v = v;
	tmp = vec_add(c.coord, c.norm);
	tmp = vec_sub(tmp, vec_scale(h, (double)P_WID / (double)2));
	tmp = vec_sub(tmp, vec_scale(v, (double)P_HEI / (double)2));
	p_info->top_left = tmp;
}

/////////////////////////////////////////////////////
t_ray	generate_ray(t_coord pos, t_p_info p_info, int i, int j)
{
	t_ray	ret;
	t_coord	tmp;

	ret.pos = pos;
	tmp = p_info.top_left;
	tmp = vec_add(tmp, vec_scale(p_info.p_h, i));
	tmp = vec_add(tmp, vec_scale(p_info.p_v, j));
	ret.dir = vec_sub(tmp, pos);
	return (ret);
}

t_rgb	get_obj_rgb(t_obj obj, t_vec lighting)
{
	t_rgb	ret;

	if (obj.type == SPHERE)
		ret = ((t_sp *)obj.object)->rgb;
	else if (obj.type == CYLINDER)
		ret = ((t_cy *)obj.object)->rgb;
	else
		ret = ((t_pl *)obj.object)->rgb;
	return (mult_rgb_vec(ret, lighting));
}

void	dot_pixel(t_img *img, t_rgb color, int i)
{
	int		pixel;

	pixel = i * 4;
	img->addr[pixel] = color.b;
	img->addr[pixel + 1] = color.g;
	img->addr[pixel + 2] = color.r;
}

t_vec	get_tangent_norm_cy(t_cy *cy, t_coord p)
{
	double	a;
	double	b;
	t_coord	t_c;

	a = vec_dot(p, cy->norm);
	b = vec_dot(vec_add(cy->coord, vec_scale(cy->norm, cy->height)), cy->norm);
	if (fabs(a - b) < 1e-6)
		return (cy->norm);
	b = vec_dot(cy->coord, cy->norm);
	if (fabs(a - b) < 1e-6)
		return (vec_scale(cy->norm, -1));
	t_c = vec_add(cy->coord, vec_scale(cy->norm, fabs(a - b)));
	return (vec_normalize(vec_sub(p, t_c)));
}

t_vec	get_tangent_norm(t_obj	obj, t_coord p)
{
	t_vec	n;

	if (obj.type == SPHERE)
		n = vec_normalize(vec_sub(p, ((t_sp *)obj.object)->coord));
	else if (obj.type == CYLINDER)
		n = get_tangent_norm_cy(obj.object, p);
	else
		n = ((t_pl *)obj.object)->norm;
	return (n);
}

int	trace_ray(t_img *img, t_world *world, t_ray ray, int i)
{
	t_obj	obj;
	t_ray	l_ray;
	t_rgb	color;
	t_coord	p;
	t_vec	n;

	if (!intersect(ray, *world, &obj))
		return (0);
	//background color
	p = vec_add(ray.pos, vec_scale(ray.dir, obj.t));
	n = get_tangent_norm(obj, p);
	color = get_obj_rgb(obj,
		compute_lighting(p, n, vec_neg(vec_normalize(ray.dir)), *world));
	dot_pixel(img, color, i);
	return (0);
}
/////////////////////////////////////////////////////

int draw_img(t_world *world, t_vars *vars)
{
	t_p_info	p_info;
	t_ray		ray;
	int			i;
	int			j;

	get_pixel_info(world->c, &p_info);
	j = -1;
	while (++j < P_HEI)
	{
		i = -1;
		while (++i < P_WID)
		{
			ray = generate_ray(world->c.coord, p_info, i, j);
			trace_ray(&vars->img, world, ray, j * P_WID + i);
		}
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.ptr, 0, 0);
	return (1);
}

int	main(int argc, char **argv)
{
	int			fd;
	t_world		world;
	t_vars		vars;

	if (argc != 2)
		return (0); // call error handling function with proper error message.
	init_mlx_pointers(&vars);
	fd = open_file(argv[1]);
	if (fd < 0) // remove this when error handling function is completed.
		return (0); // 에러 문자열 출력하고 처리해주기
	world.l = 0;
	world.sp = 0;
	world.pl = 0;
	world.cy = 0;
	if (read_file(fd, &world))
		printf("%s\n", "valid format");
	else
		printf("%s\n", "invalid format");
	/* draw image */
	draw_img(&world, &vars);
	clear_list(&(world.l));
	clear_list(&(world.sp));
	clear_list(&(world.pl));
	clear_list(&(world.cy));
	mlx_loop(vars.mlx);
	return (0);
}