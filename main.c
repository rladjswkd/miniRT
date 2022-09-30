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

void	free_splitted(char **splitted)
{
	int	i;

	i = -1;
	while (splitted[++i])
		free(splitted[i]);
	free(splitted);
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
		return (0);
	free_splitted(rgb_info);
	if (!check_rgb(*rgb))
		return (0);
	return (1);
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
		return (0);
	free_splitted(coord_info);
	return (1);
}

int	set_ambient(char **info, t_ambient *a) // caller must check whether the count of splitted is 3. and this function is called only if splitted[0] is "A"
{
	double	intensity;
	t_rgb	rgb;

	if (!get_double(info[1], &intensity)
		|| intensity < 0 || 1 < intensity
		|| !check_comma_cnt(info[2]))
		return (0);
	if (!set_rgb(info[2], &rgb))
		return (0);
	a->intensity = intensity;
	a->rgb.r = rgb.r;
	a->rgb.g = rgb.g;
	a->rgb.b = rgb.b;
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
	char		*str1 = "A 0.2 255,255,255";
	char		*str2 = "A 0.0 255,255,255";
	char		*str3 = "A -0.1 255,255,255";
	char		*str4 = "A 1.2 255,255,255";
	char		*str5 = "A 0.2 256,255,255";
	char		*str6 = "A 0.2 255,-1,255";
	char		*str7 = "A 0.2 255,255,4242";
	char		*str8 = "A 0.2 1,1,1";
	char		*str9 = "A 0.2 1, 1, 1";

	t_ambient	a;
	char		**splitted;
	int			count;

	splitted = split_line(str1, ' ', &count);
	if (set_ambient(splitted, &a))
		printf("intensity : %f, r,g,b: %d, %d, %d\n", a.intensity, a.rgb.r, a.rgb.g, a.rgb.b);
	free_splitted(splitted);
	splitted = split_line(str2, ' ', &count);
	if (set_ambient(splitted, &a))
		printf("intensity : %f, r,g,b: %d, %d, %d\n", a.intensity, a.rgb.r, a.rgb.g, a.rgb.b);
	free_splitted(splitted);
	splitted = split_line(str3, ' ', &count);
	if (set_ambient(splitted, &a))
		printf("intensity : %f, r,g,b: %d, %d, %d\n", a.intensity, a.rgb.r, a.rgb.g, a.rgb.b);
	free_splitted(splitted);
	splitted = split_line(str4, ' ', &count);
	if (set_ambient(splitted, &a))
		printf("intensity : %f, r,g,b: %d, %d, %d\n", a.intensity, a.rgb.r, a.rgb.g, a.rgb.b);
	free_splitted(splitted);
	splitted = split_line(str5, ' ', &count);
	if (set_ambient(splitted, &a))
		printf("intensity : %f, r,g,b: %d, %d, %d\n", a.intensity, a.rgb.r, a.rgb.g, a.rgb.b);
	free_splitted(splitted);
	splitted = split_line(str6, ' ', &count);
	if (set_ambient(splitted, &a))
		printf("intensity : %f, r,g,b: %d, %d, %d\n", a.intensity, a.rgb.r, a.rgb.g, a.rgb.b);
	free_splitted(splitted);
	splitted = split_line(str7, ' ', &count);
	if (set_ambient(splitted, &a))
		printf("intensity : %f, r,g,b: %d, %d, %d\n", a.intensity, a.rgb.r, a.rgb.g, a.rgb.b);
	free_splitted(splitted);
	splitted = split_line(str8, ' ', &count);
	if (set_ambient(splitted, &a))
		printf("intensity : %f, r,g,b: %d, %d, %d\n", a.intensity, a.rgb.r, a.rgb.g, a.rgb.b);
	free_splitted(splitted);
	splitted = split_line(str9, ' ', &count);
	if (set_ambient(splitted, &a))
		printf("intensity : %f, r,g,b: %d, %d, %d\n", a.intensity, a.rgb.r, a.rgb.g, a.rgb.b);
	free_splitted(splitted);
	return (0);
}