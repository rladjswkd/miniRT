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
/*
추가
구, 원기둥, 평면과 광선의 교점에서의 t를 찾는 함수들 및 그에 필요한 여러 구조체들 (t는 광선에 대한 식인 o + td에서의 t. o와 d는 각각 광원의 위치, 광선의 방향 벡터)
*/

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
	double	t1;
	double	t2;
}	t_inter;

typedef struct s_circle
{
	t_coord	center;
	double	radius;
}	t_circle;

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

int	intersect_circle(t_ray ray, t_circle cir, t_inter *inter)
{
	double		a;
	double		b;
	double		c;
	double		discriminant;
	t_vec		origin_to_center;

	origin_to_center = vec_sub(ray.pos, cir.center);
	a = vec_dot(ray.dir, ray.dir);
	b = 2 * vec_dot(origin_to_center, ray.dir);
	c = vec_dot(origin_to_center, origin_to_center) - pow(cir.radius, 2);
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (0);
	inter->t1 = (-b - sqrt(discriminant)) / (2 * a); // smaller
	inter->t2 = (-b + sqrt(discriminant)) / (2 * a); // bigger
	return (1);
}

int	get_min_intersection(double *ret, t_inter i)
{
	if (i.t1 <= 1 && i.t2 <= 1)
		return (0);
	*ret = i.t2;
	if (i.t1 > 1)
		*ret = i.t1;
	return (1);
}

int	intersect_sphere(t_ray ray, t_sp sp, double	*t)
{
	t_inter		*i;
	t_circle	p;

	p.center = sp.coord;
	p.radius = sp.diameter / 2;
	return (intersect_circle(ray, p, i) && get_min_intersection(t, *i));
}

t_vec	ray_pos(t_ray ray, double t)
{
	return (vec_add(ray.pos, vec_scale(ray.dir, t)));
}

int	intersect_body(t_ray ray, t_cy cy, t_inter *inter)
{
	t_vec		c_perp;
	t_ray		r_perp;
	double		proj_t1;
	double		proj_t2;

	c_perp = vec_sub(cy.coord, vec_proj(cy.coord, cy.norm));
	r_perp.pos = vec_sub(ray.pos, vec_proj(ray.pos, cy.norm));
	r_perp.dir = vec_sub(ray.dir, vec_proj(ray.dir, cy.norm));
	if (!intersect_circle(r_perp, (t_circle){c_perp, cy.diameter / 2}, inter))
		return (0);
	proj_t1 = vec_len(vec_proj(vec_sub(ray_pos(ray, inter->t1), cy.coord), cy.norm));
	proj_t2 = vec_len(vec_proj(vec_sub(ray_pos(ray, inter->t2), cy.coord), cy.norm));
	if (proj_t1 < 0 || cy.height < proj_t1)
		inter->t1 = -1;
	if (proj_t2 < 0 || cy.height < proj_t2)
		inter->t2 = -1;
	return (1);
}

int	intersect_caps(t_ray ray, t_cy cy, t_inter *inter)
{
	double	bottom;
	double	top;
	double	c_to_t1;
	double	c_to_t2;
	double	radius;

	bottom = vec_len(vec_proj(cy.coord, cy.norm));
	top = bottom + cy.height;
	inter->t1 = (bottom - vec_len(vec_proj(ray.pos, cy.norm)))
		/ vec_len(vec_proj(ray.dir, cy.norm));
	inter->t2 = (top - vec_len(vec_proj(ray.pos, cy.norm)))
		/ vec_len(vec_proj(ray.dir, cy.norm));
	c_to_t1 = vec_len(vec_sub(ray_pos(ray, inter->t1), cy.coord));
	c_to_t2 = vec_len(vec_sub(ray_pos(ray, inter->t2), vec_add(
			cy.coord, vec_scale(cy.norm, cy.height))));
	radius = cy.diameter / 2;
	if (c_to_t1 >= radius && c_to_t2 >= radius)
		return (0);
	if (c_to_t1 >= radius)
		inter->t1 = -1;
	if (c_to_t2 >= radius)
		inter->t2 = -1;
	return (1);
}

int	intersect_cylinder(t_ray ray, t_cy cy, double *t) // ray랑 normal이랑 평행한 지 확인해야 한다., get_min_intersection을 체크하는 함수 포인터를 전달한다.
{
	t_inter	inter1;
	t_inter	inter2;
	double	t1;
	double	t2;

	if (fabs(vec_len(vec_proj(vec_normalize(ray.dir), cy.norm)) - 1) < 1e-6)
	{
		if (!intersect_caps(ray, cy, &inter2)
			|| !get_min_intersection(&t2, inter2))
			return (0);
		*t = t2;
		return (1);
	}
	if (!intersect_body(ray, cy, &inter1))
		return (0);
	get_min_intersection(&t1, inter1);
	inter2.t1 = 0;
	inter2.t2 = 0;
	intersect_caps(ray, cy, &inter2);
	get_min_intersection(&t2, inter2);
	if (!get_min_intersection(t, (t_inter){t1, t2}))
		return (0);
	return (1);		
}
// unit vector check
// cylinder is infinite.


int	intersect_plane(t_ray ray, t_pl pl, double *t)
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

int	check_shadow_sp(t_ray ray, t_node *sp)
{
	double	cur;

	cur = 2;
	if (!sp)
		return (0);
	while (sp->data)
	{
		if (intersect_sphere(ray, *((t_sp *)(sp->data)), &cur) && cur < 2)
			return (1);
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
	while (cy->data)
	{
		if (intersect_cylinder(ray, *((t_cy *)(cy->data)), &cur) && cur < 2)
			return (1);
	}
	return (0);
}

int	check_shadow_pl(t_ray ray, t_node *pl)
{
	double	cur;

	cur = 2;
	if (!pl)
		return (0);
	while (pl->data)
	{
		if (intersect_plane(ray, *((t_pl *)(pl->data)), &cur) && cur < 2)
			return (1);
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

int	check_shadow(t_rt_info info, t_ray l_ray)
{
	if (check_shadow_sp(l_ray, info.sp))
		return (1);
	if (check_shadow_cy(l_ray, info.cy))
		return (1);
	if (check_shadow_pl(l_ray, info.pl))
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

t_rgb	get_obj_rgb(t_obj obj, double intensity)
{
	t_rgb	ret;

	if (obj.type == SPHERE)
		ret = ((t_sp *)obj.object)->rgb;
	else if (obj.type == CYLINDER)
		ret = ((t_cy *)obj.object)->rgb;
	else
		ret = ((t_pl *)obj.object)->rgb;
	ret.r = ret.r * intensity;
	ret.g = ret.g * intensity;
	ret.b = ret.b * intensity;
	return (ret);
}

void	dot_pixel(t_img *img, t_rgb color, int i)
{
	int	pixel;

	pixel = i * 4;
	img->addr[pixel] = color.r;
	img->addr[pixel + 1] = color.g;
	img->addr[pixel + 2] = color.b;
}

int	ray_trace(t_img *img, t_rt_info *rt_info, t_ray ray, int i)
{
	t_obj	obj;
	t_ray	l_ray;
	t_rgb	color;

	if (intersect(ray, *rt_info, &obj))
		return (0);
	l_ray = get_l_ray(rt_info->l, ray, obj);
	if (check_shadow(*rt_info, l_ray))
	{
		//default
		return (0);
	}
	color = get_obj_rgb(obj, rt_info->a.intensity);
	dot_pixel(img, color, i);
	return (0);
}
/////////////////////////////////////////////////////

int draw_img(t_rt_info *rt_info, t_vars *vars)
{
	t_p_info	p_info;
	t_ray		ray;
	int			i;
	int			j;

	get_pixel_info(rt_info->c, &p_info);
	i = -1;
	while (++i < P_HEI)
	{
		j = -1;
		while (++j < P_WID)
		{
			ray = generate_ray(rt_info->c.coord, p_info, i, j);
			ray_trace(&vars->img, rt_info, ray, i * P_HEI + j);
		}
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.ptr, 0, 0);
	return (1);
}

int	main(int argc, char **argv)
{
	int			fd;
	t_rt_info	rt_info;
	t_vars		vars;

	if (argc != 2)
		return (0); // call error handling function with proper error message.
	init_mlx_pointers(&vars);
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
	draw_img(&rt_info, &vars);
	clear_list(&(rt_info.sp));
	clear_list(&(rt_info.pl));
	clear_list(&(rt_info.cy));
	mlx_loop(vars.mlx);
	return (0);
}