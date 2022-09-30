#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"
#include "string_utils.h"
#include "parser_util_split.h"
#include <math.h>
#include "converter.h"

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
	int		i;
	double	d;

	printf("%d\n", get_int("-2147483648.0", &i));
	printf("%d\n", i);
	printf("\n");
	printf("%d\n", get_int("-2147483-", &i));
	printf("%d\n", i);
	printf("\n");
	printf("%d\n", get_int("-2147483649", &i));
	printf("%d\n", i);
	printf("\n");
	printf("%d\n", get_int("-2147483648", &i));
	printf("%d\n", i);
	printf("\n");
	printf("%d\n", get_int("-1", &i));
	printf("%d\n", i);
	printf("\n");
	printf("%d\n", get_int("0", &i));
	printf("%d\n", i);
	printf("\n");
	printf("%d\n", get_int("1", &i));
	printf("%d\n", i);
	printf("\n");
	printf("%d\n", get_int("2147483647", &i));
	printf("%d\n", i);
	printf("\n");
	printf("%d\n", get_int("2147483648", &i));
	printf("%d\n", i);
	printf("\n");
	printf("%d\n", get_double("-2147483648.0", &d));
	printf("%f\n", d);
	printf("\n");
	printf("%d\n", get_double("-1.0", &d));
	printf("%f\n", d);
	printf("\n");
	printf("%d\n", get_double("-1", &d));
	printf("%f\n", d);
	printf("\n");
	printf("%d\n", get_double("0.0", &d));
	printf("%f\n", d);
	printf("\n");
	printf("%d\n", get_double("0", &d));
	printf("%f\n", d);
	printf("\n");
	printf("%d\n", get_double("1.0", &d));
	printf("%f\n", d);
	printf("\n");
	printf("%d\n", get_double("1", &d));
	printf("%f\n", d);
	printf("\n");
	printf("%d\n", get_double("1.", &d));
	printf("%f\n", d);
	printf("\n");
	printf("%d\n", get_double("0.1", &d));
	printf("%f\n", d);
	printf("\n");
	printf("%d\n", get_double(".1", &d));
	printf("%f\n", d);
	printf("\n");
	printf("%d\n", get_double("0.999999", &d));
	printf("%f\n", d);
	printf("\n");
	printf("%d\n", get_double("2147483647.234567", &d));
	printf("%f\n", d);

	return (0);
}