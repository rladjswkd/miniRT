#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"
#include "string_utils.h"
#include "parser_util_split.h"
#include <math.h>
#include "converter.h"
#include "checker.h"

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
}	t_coordinate;

typedef	t_coordinate	t_vector;

typedef struct s_ambient
{
	double	intensity;
	t_rgb	rgb;
}	t_ambient;

typedef struct s_light
{
	t_coordinate	coordinate;
	double			intensity;
	t_rgb			rgb;
}	t_light;


typedef struct s_camera
{
	t_coordinate	coordinate;
	t_vector		normalized;
	int				fov;
}	t_camera;

typedef struct s_sphere
{
	t_coordinate	coordinate;
	double			diameter;
	t_rgb			rgb;
}	t_sphere;

typedef struct s_plane
{
	t_coordinate	coordinate;
	t_vector		normalized;
	t_rgb			rgb;
}	t_plane;

typedef struct s_cylinder
{
	t_coordinate	coordinate;
	t_vector		normalized;
	double			diameter;
	double			height;
	t_rgb			rgb;
}	t_cylinder;

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

int	check_normal(t_vector vec)
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

int	set_coordinate(char *coord_str, t_coordinate *coord)
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
	if (!set_coordinate(info[1], &(l->coordinate)))
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
	if (!set_coordinate(info[1], &(c->coordinate)))
		return (0);
	if (!set_coordinate(info[2], &(c->normalized))
		|| !check_normal(c->normalized))
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
	t_plane	*pl;

	if (cnt != 4)
		return (0);
	pl = (t_plane *)(get_last_node(rt_info->pl)->data);
	if (!set_coordinate(info[1], &(pl->coordinate)))
		return (0);
	if (!set_coordinate(info[2], &(pl->normalized))
		|| !check_normal(pl->normalized))
		return (0);
	if (!set_rgb(info[3], &(pl->rgb)))
		return (0);
	return (1);
}

int	set_sphere(char **info, int cnt, t_rt_info *rt_info)
{
	double		diameter;
	t_sphere	*sp;

	if (cnt != 4)
		return (0);
	sp = (t_sphere *)(get_last_node(rt_info->sp)->data);
	if (!set_coordinate(info[1], &(sp->coordinate)))
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
	double		diameter;
	double		height;
	t_cylinder	*cy;

	if (cnt != 6)
		return (0);
	cy = (t_cylinder *)(get_last_node(rt_info->cy)->data);
	if (!set_coordinate(info[1], &(cy->coordinate)))
		return (0);
	if (!set_coordinate(info[2], &(cy->normalized))
		|| !check_normal(cy->normalized))
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
	t_sphere	*sp;
	
	sp = (t_sphere *)malloc(sizeof(t_sphere));
	if (!sp)
		return (0);
	*ptr = (void *)sp;
	return (1);
}

int	alloc_plane(void **ptr){
	t_plane	*pl;
	
	pl = (t_plane *)malloc(sizeof(t_plane));
	if (!pl)
		return (0);
	*ptr = (void *)pl;
	return (1);
}

int	alloc_cylinder(void **ptr){
	t_cylinder	*cy;
	
	cy = (t_cylinder *)malloc(sizeof(t_cylinder));
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
	// t_node 동적 할당, index에 맞는 오브젝트의 구조체 동적 할당, 할당한 것들을 index에 해당하는 t_rt_info 구조체의 멤버에 할당하는 함수 필요.
	// set_{sp, pl, cy}에서 t_rt_info 구조체 내의 sp, pl, cy 노드 중 가장 마지막 노드를 가져와서 그 노드의 data에 대해 작업하는 코드 필요.
	// fp가 0을 반환하면 위에 할당한 것들을 모두 해제하는 함수 필요.
	// 이 부분에 해당하는 내용을 아예 함수 하나로 빼자.
	if (2 < index
		&& (!set_object_list(rt, index)	|| !(*fp[index])(splitted, cnt, rt)))
		return (free_splitted(splitted, 0));
	return (1);
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
	return (0);
}