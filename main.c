#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

typedef struct	s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

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

int	get_len(char *str)
{
	int	len;

	while (str[len])
		len++;
	return (len);
}

int	open_file(char *path)
{
	int	fd;
	int	len;

	fd = -1;
	len = get_len(path);
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
	t_rgb	rgb1 = {0, 0, 0};
	t_rgb	rgb2 = {-1, 0, 0};
	t_rgb	rgb3 = {255, 255, 255};
	t_rgb	rgb4 = {0, 0, 256};
	t_rgb	rgb5 = {255, 9999999999999999999, 255}; // can be ok if overflow-ed value of 999... is valid for int.

	printf("%d\n", check_rgb(rgb1));
	printf("%d\n", check_rgb(rgb2));
	printf("%d\n", check_rgb(rgb3));
	printf("%d\n", check_rgb(rgb4));
	printf("%d\n", check_rgb(rgb5));
	return (0);
}