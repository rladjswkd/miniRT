#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"
#include "string_utils.h"
#include "parser_util_split.h"
#include <math.h>
#include "converter.h"
int	check_comma_cnt(char *s); // should be removed.

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

int	set_ambient(char **info, t_ambient *a) // caller must check whether the count of splitted is 3. and this function is called only if splitted[0] is "A"
{
	double	intensity;
	t_rgb	rgb;

	if (!get_double(info[1], &intensity)
		|| intensity < 0 || 1 < intensity)
		return (0);
	if (!set_rgb(info[2], &rgb))
		return (0);
	a->intensity = intensity;
	a->rgb.r = rgb.r;
	a->rgb.g = rgb.g;
	a->rgb.b = rgb.b;
	return (1);
}

int	set_light(char **info, t_light *l)// caller must check whether the count of splitted is 4. and this function is called only if splitted[0] is "L"
{
	t_coordinate	coordinate;
	double			intensitiy;
	t_rgb			rgb;

	if (!set_coordinate(info[1], &coordinate))
		return (0);
	if (!get_double(info[2], &intensitiy)
		|| intensitiy < 0 || 1 < intensitiy)
		return (0);
	if (!set_rgb(info[3], &rgb))
		return (0);
	l->coordinate.x = coordinate.x;
	l->coordinate.y = coordinate.y;
	l->coordinate.z = coordinate.z;
	l->intensity = intensitiy;
	l->rgb.r = rgb.r;
	l->rgb.g = rgb.g;
	l->rgb.b = rgb.b;
	return (1);
}


int	set_camera(char **info, t_camera *c)// caller must check whether the count of splitted is 4. and this function is called only if splitted[0] is "C"
{
	t_coordinate	coordinate;
	t_vector		normalized;
	int				fov;

	if (!set_coordinate(info[1], &coordinate))
		return (0);
	if (!set_coordinate(info[2], &normalized)
		|| !check_normal(normalized))
		return (0);
	if (!get_int(info[3], &fov)
		|| fov < 0 || 180 < fov) // 180 0
		return (0);
	c->coordinate.x = coordinate.x;
	c->coordinate.y = coordinate.y;
	c->coordinate.z = coordinate.z;
	c->normalized.x = normalized.x;
	c->normalized.y = normalized.y;
	c->normalized.z = normalized.z;
	c->fov = fov;
	return (1);
}

int	set_plane(char **info, t_plane *pl)// caller must check whether the count of splitted is 4. and this function is called only if splitted[0] is "pl"
{
	t_coordinate	coordinate;
	t_vector		normalized;
  t_rgb			rgb;

	if (!set_coordinate(info[1], &coordinate))
		return (0);
  if (!set_coordinate(info[2], &normalized)
	|| !check_normal(normalized))
		return (0);
	if (!set_rgb(info[3], &rgb))
		return (0);
	pl->coordinate.x = coordinate.x;
	pl->coordinate.y = coordinate.y;
	pl->coordinate.z = coordinate.z;
	pl->normalized.x = normalized.x;
	pl->normalized.y = normalized.y;
	pl->normalized.z = normalized.z;
	pl->rgb.r = rgb.r;
	pl->rgb.g = rgb.g;
	pl->rgb.b = rgb.b;
  return (1);
}

int	set_sphere(char **info, t_sphere *sp)// caller must check whether the count of splitted is 4. and this function is called only if splitted[0] is "sp"
{
	t_coordinate	coordinate;
	double			diameter;
  t_rgb			rgb;

	if (!set_coordinate(info[1], &coordinate))
		return (0);
	if (!get_double(info[2], &diameter)
		|| diameter < 0)
		return (0);
	if (!set_rgb(info[3], &rgb))
		return (0);
	sp->coordinate.x = coordinate.x;
	sp->coordinate.y = coordinate.y;
	sp->coordinate.z = coordinate.z;
	sp->diameter = diameter;
	sp->rgb.r = rgb.r;
	sp->rgb.g = rgb.g;
	sp->rgb.b = rgb.b;
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

int	main(int argc, char **argv)
{
	// int		fd;
	// char	*p;

	// if (argc != 2)
	// 	return (0); // call error handling function with proper error message.
	// fd = open_file(argv[1]);
	// if (fd < 0) // remove this when error handling function is completed.
	// 	return (0); // 에러 문자열 출력하고 처리해주기
	// while (1)
	// {
	// 	p = get_next_line(fd);
	// 	if (p == 0)
	// 		break ;
	// 	if (p[0] != '\0')
	// 		printf("%s\n", p); // 유효성 검사 수행하는 함수 호출
	// 	free(p);
	// }

	char		*str1 = "pl 0.0,0.0,-10.0 0.0,1.0,0.0 0,0,225";
 	char		*str2 = "pl 0.1,0.0,-10.0 0.0,1.0,0.0 0,0,225";
 	char		*str3 = "pl 0.2,0.0,-10.0 0.0,1.0,0.0 -12,0,225";
 	char		*str4 = "pl 0.3,0.0,-10.0 0.0,1.0,-0.0 0,0,225";
 	char		*str5 = "pl 0.4,0.0,-10.0 0.0,1.0,0.0 0,0,225";

 	t_plane	pl;
 	char		**splitted;
 	int			count;

 	splitted = split_line(str1, ' ', &count);
 	if (set_plane(splitted, &pl))
 		printf("coordinate x,y,z: %f, %f, %f normalized:%f, %f, %f RGB r,g,b: %d, %d, %d\n", pl.coordinate.x, pl.coordinate.y, pl.coordinate.z, pl.normalized.x, pl.normalized.y, pl.normalized.z, pl.rgb.r, pl.rgb.g, pl.rgb.b);
 	free_splitted(splitted);
 	splitted = split_line(str2, ' ', &count);
 	if (set_plane(splitted, &pl))
 		printf("coordinate x,y,z: %f, %f, %f normalized:%f, %f, %f RGB r,g,b: %d, %d, %d\n", pl.coordinate.x, pl.coordinate.y, pl.coordinate.z, pl.normalized.x, pl.normalized.y, pl.normalized.z, pl.rgb.r, pl.rgb.g, pl.rgb.b);
 	free_splitted(splitted);
 	splitted = split_line(str3, ' ', &count);
 	if (set_plane(splitted, &pl))
 		printf("oordinate x,y,z: %f, %f, %f normalized:%f, %f, %f RGB r,g,b: %d, %d, %d\n", pl.coordinate.x, pl.coordinate.y, pl.coordinate.z, pl.normalized.x, pl.normalized.y, pl.normalized.z, pl.rgb.r, pl.rgb.g, pl.rgb.b);
 	free_splitted(splitted);
 	splitted = split_line(str4, ' ', &count);
 	if (set_plane(splitted, &pl))
 		printf("oordinate x,y,z: %f, %f, %f normalized:%f, %f, %f RGB r,g,b: %d, %d, %d\n", pl.coordinate.x, pl.coordinate.y, pl.coordinate.z, pl.normalized.x, pl.normalized.y, pl.normalized.z, pl.rgb.r, pl.rgb.g, pl.rgb.b);
 	free_splitted(splitted);
 	splitted = split_line(str5, ' ', &count);
 	if (set_plane(splitted, &pl))
 		printf("oordinate x,y,z: %f, %f, %f normalized:%f, %f, %f RGB r,g,b: %d, %d, %d\n", pl.coordinate.x, pl.coordinate.y, pl.coordinate.z, pl.normalized.x, pl.normalized.y, pl.normalized.z, pl.rgb.r, pl.rgb.g, pl.rgb.b);
 	free_splitted(splitted);

	return (0);
}