// #include <stdio.h>
// #include <fcntl.h>
// #include "get_next_line.h"
// #include "string_utils.h"
// #include "parser_util_split.h"
// #include <math.h>
// #include "converter.h"
// #include "checker.h"
// /*
// set_* 함수들에서 구조체 메모리 영역에 접근하는 횟수를 최소로 만들 수 있는 경우에 대해서만 지역 변수에 값을 할당한 후 구조체 멤버에 지역 변수의 값을 재할당하는 방식을 사용하도록 수정.
// if 문의 조건식이 80자가 넘지 않을 때, 한 줄에 적도록 수정.

// */
// typedef struct s_rgb
// {
// 	int	r;
// 	int	g;
// 	int	b;
// }	t_rgb;

// typedef struct s_coordinate
// {
// 	double	x;
// 	double	y;
// 	double	z;
// }	t_coord;

// typedef	t_coord	t_vec;

// typedef struct s_ambient
// {
// 	double	intensity;
// 	t_rgb	rgb;
// }	t_ambient;

// typedef struct s_light
// {
// 	t_coord	coordinate;
// 	double			intensity;
// 	t_rgb			rgb;
// }	t_light;


// typedef struct s_camera
// {
// 	t_coord	coordinate;
// 	t_vec		normalized;
// 	int				fov;
// }	t_camera;

// typedef struct s_sphere
// {
// 	t_coord	coordinate;
// 	double			diameter;
// 	t_rgb			rgb;
// }	t_sp;

// typedef struct s_plane
// {
// 	t_coord	coordinate;
// 	t_vec		normalized;
// 	t_rgb			rgb;
// }	t_pl;

// typedef struct s_cylinder
// {
// 	t_coord	coordinate;
// 	t_vec		normalized;
// 	double			diameter;
// 	double			height;
// 	t_rgb			rgb;
// }	t_cy;

// typedef struct s_node
// {
// 	void			*data;
// 	struct s_node	*next;
// }	t_node;

// typedef struct s_rt_info
// {
// 	t_ambient	a;
// 	t_camera	c;
// 	t_light		l;
// 	t_node		*sp;
// 	t_node		*cy;
// 	t_node		*pl;
// }	t_rt_info;

// int	check_rgb(t_rgb rgb)
// {
// 	int	r;
// 	int	g;
// 	int	b;

// 	r = rgb.r;
// 	g = rgb.g;
// 	b = rgb.b;
// 	return (-1 < r && r < 256 && -1 < g && g < 256 && -1 < b && b < 256);
// }

// int	check_normal(t_vec vec)
// {
// 	double	x;
// 	double	y;
// 	double	z;

// 	x = vec.x;
// 	y = vec.y;
// 	z = vec.z;
// 	return (-1 <= x && x <= 1 && -1 <= y && y <= 1 && -1 <= z && z <= 1
// 		&& sqrt(x * x + y * y + z * z) == 1);
// }

// int	free_splitted(char **splitted, int ret)
// {
// 	int	i;

// 	i = -1;
// 	while (splitted[++i])
// 		free(splitted[i]);
// 	free(splitted);
// 	return (ret);
// }

// int	set_rgb(char *rgb_str, t_rgb *rgb)
// {
// 	char	**rgb_info;
// 	int		rgb_info_cnt;

// 	if (!check_comma_cnt(rgb_str))
// 		return (0);
// 	rgb_info = split_line(rgb_str, ',', &rgb_info_cnt);
// 	if (rgb_info_cnt != 3
// 		|| !get_int(rgb_info[0], &(rgb->r))
// 		|| !get_int(rgb_info[1], &(rgb->g))
// 		|| !get_int(rgb_info[2], &(rgb->b)))
// 		return (free_splitted(rgb_info, 0));
// 	if (!check_rgb(*rgb))
// 		return (free_splitted(rgb_info, 0));
// 	return (free_splitted(rgb_info, 1));
// }

// int	set_coordinate(char *coord_str, t_coord *coord)
// {
// 	char	**coord_info;
// 	int		coord_info_cnt;

// 	if (!check_comma_cnt(coord_str))
// 		return (0);
// 	coord_info = split_line(coord_str, ',', &coord_info_cnt);
// 	if (coord_info_cnt != 3
// 		|| !get_double(coord_info[0], &(coord->x))
// 		|| !get_double(coord_info[1], &(coord->y))
// 		|| !get_double(coord_info[2], &(coord->z)))
// 		return (free_splitted(coord_info, 0));
// 	return (free_splitted(coord_info, 1));
// }

// int	set_ambient(char **info, t_ambient *a) // caller must check whether the count of splitted is 3. and this function is called only if splitted[0] is "A"
// {
// 	double	intensity;

// 	if (!get_double(info[1], &intensity) || intensity < 0 || 1 < intensity)
// 		return (0);
// 	if (!set_rgb(info[2], &(a->rgb)))
// 		return (0);
// 	a->intensity = intensity;
// 	return (1);
// }

// int	set_light(char **info, t_light *l)// caller must check whether the count of splitted is 4. and this function is called only if splitted[0] is "L"
// {
// 	double	intensitiy;

// 	if (!set_coordinate(info[1], &(l->coordinate)))
// 		return (0);
// 	if (!get_double(info[2], &intensitiy) || intensitiy < 0 || 1 < intensitiy)
// 		return (0);
// 	if (!set_rgb(info[3], &(l->rgb)))
// 		return (0);
// 	l->intensity = intensitiy;
// 	return (1);
// }

// int	set_camera(char **info, t_camera *c)// caller must check whether the count of splitted is 4. and this function is called only if splitted[0] is "C"
// {
// 	int	fov;

// 	if (!set_coordinate(info[1], &(c->coordinate)))
// 		return (0);
// 	if (!set_coordinate(info[2], &(c->normalized)
// 		|| !check_normal(c->normalized)))
// 		return (0);
// 	if (!get_int(info[3], &fov)	|| fov < 0 || 180 < fov) // 180 0
// 		return (0);
// 	c->fov = fov;
// 	return (1);
// }

// int	set_plane(char **info, t_pl *pl)// caller must check whether the count of splitted is 4. and this function is called only if splitted[0] is "pl"
// {
// 	if (!set_coordinate(info[1], &(pl->coordinate)))
// 		return (0);
// 	if (!set_coordinate(info[2], &(pl->normalized))
// 		|| !check_normal(pl->normalized))
// 		return (0);
// 	if (!set_rgb(info[3], &(pl->rgb)))
// 		return (0);
// 	return (1);
// }

// int	set_sphere(char **info, t_sp *sp)// caller must check whether the count of splitted is 4. and this function is called only if splitted[0] is "sp"
// {
// 	double	diameter;

// 	if (!set_coordinate(info[1], &(sp->coordinate)))
// 		return (0);
// 	if (!get_double(info[2], &diameter) || diameter < 0)
// 		return (0);
// 	if (!set_rgb(info[3], &(sp->rgb)))
// 		return (0);
// 	sp->diameter = diameter;
// 	return (1);
// }

// int	set_cylinder(char **info, t_cy *cy)// caller must check whether the count of splitted is 6. and this function is called only if splitted[0] is "cy"
// {
// 	double	diameter;
// 	double	height;

// 	if (!set_coordinate(info[1], &(cy->coordinate)))
// 		return (0);
// 	if (!set_coordinate(info[2], &(cy->normalized))
// 		|| !check_normal(cy->normalized))
// 		return (0);
// 	if (!get_double(info[3], &diameter) || diameter < 0)
// 		return (0);
// 	if (!get_double(info[4], &height) || height < 0)
// 		return (0);
// 	if (!set_rgb(info[5], &(cy->rgb)))
// 	cy->diameter = diameter;
// 	cy->height = height;
// 	return (1);
// }

// int	set_rt_info(char *line, t_rt_info *rt_info)
// {
// 	char	**splitted;
// 	int		count;

// 	splitted = split_line(line, ' ', &count); // should null-guard be for split_lines...?

// }

// int	open_file(char *path)
// {
// 	int	fd;
// 	int	len;

// 	fd = -1;
// 	len = ft_strlen(path);
// 	if (path[len - 3] == '.' && path[len - 2] == 'r' && path[len - 1] == 't')
// 		fd = open(path, O_RDONLY); // is read-only enough?
// 	// call error handling function to exit.
// 	return (fd);
// }

// int	read_file(int fd, t_rt_info *rt_info)
// {
// 	char	*line;
// 	int		flag;

// 	flag = 1;
// 	while (flag)
// 	{
// 		line = get_next_line(fd);
// 		if (line == 0)
// 			break ;
// 		if (line[0] != '\0')
// 			flag = set_rt_info(line, rt_info);
// 		free(line);
// 	}
// }

// int	main(int argc, char **argv)
// {
// 	// int		fd;
// 	// char	*p;

// 	// if (argc != 2)
// 	// 	return (0); // call error handling function with proper error message.
// 	// fd = open_file(argv[1]);
// 	// if (fd < 0) // remove this when error handling function is completed.
// 	// 	return (0); // 에러 문자열 출력하고 처리해주기
// 	// while (1)
// 	// {
// 	// 	p = get_next_line(fd);
// 	// 	if (p == 0)
// 	// 		break ;
// 	// 	if (p[0] != '\0')
// 	// 		printf("%s\n", p); // 유효성 검사 수행하는 함수 호출
// 	// 	free(p);
// 	// }

// 	char		*str1 = "cy 50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 10,0,255";
// 	char		*str2 = "cy 50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 10,0,255";
// 	char		*str3 = "cy 50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 10,0,255";


// 	t_cy	cy;
// 	char		**splitted;
// 	int			count;

// 	splitted = split_line(str1, ' ', &count);
// 	if (set_cylinder(splitted, &cy))
// 		printf("coordinate x,y,z: %f, %f, %f  normalized x,y,z: %f %f %f \ndiameter: %f height:%f RGB r,g,b: %d, %d, %d\n", cy.coordinate.x, cy.coordinate.y, cy.coordinate.z, cy.normalized.x, cy.normalized.y, cy.normalized.z, cy.diameter, cy.height, cy.rgb.r, cy.rgb.g, cy.rgb.b);
// 	free_splitted(splitted,0);
// 	splitted = split_line(str2, ' ', &count);
// 	if (set_cylinder(splitted, &cy))
// 		printf("coordinate x,y,z: %f, %f, %f  normalized x,y,z: %f %f %f \ndiameter: %f height:%f RGB r,g,b: %d, %d, %d\n", cy.coordinate.x, cy.coordinate.y, cy.coordinate.z, cy.normalized.x, cy.normalized.y, cy.normalized.z, cy.diameter, cy.height, cy.rgb.r, cy.rgb.g, cy.rgb.b);
// 	free_splitted(splitted,0);
// 	splitted = split_line(str3, ' ', &count);
// 	if (set_cylinder(splitted, &cy))
// 		printf("coordinate x,y,z: %f, %f, %f  normalized x,y,z: %f %f %f \ndiameter: %f height:%f RGB r,g,b: %d, %d, %d\n", cy.coordinate.x, cy.coordinate.y, cy.coordinate.z, cy.normalized.x, cy.normalized.y, cy.normalized.z, cy.diameter, cy.height, cy.rgb.r, cy.rgb.g, cy.rgb.b);
// 	free_splitted(splitted,0);

// 	return (0);
// }