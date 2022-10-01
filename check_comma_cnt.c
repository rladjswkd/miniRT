#include <stdio.h>

int	check_comma_cnt(char *s)
{
	int		i;
	char	c;

	i = 0;
	c = ',';
	if (s[0] == c)
		return (0);
	while (s[++i])
	{
		if (s[i] == c && s[i + 1] == c)
			return (0);
	}
	if (s[i - 1] == c)
		return (0);
	return (1);
}

// int	main(void) 
// {
// 	printf(",doblue,double,double:	%d\n", check_comma_cnt(",doblue,double,double"));
// 	printf("double,double,double,:	%d\n", check_comma_cnt("double,double,double,"));
// 	printf("double,double,double:	%d\n", check_comma_cnt("double,double,double"));
// 	printf("double,,double,double:	%d\n", check_comma_cnt("double,,double,double"));
// 	printf("double,double,double,double:	%d\n", check_comma_cnt("double,double,double,double"));
// 	printf("double,double:		%d\n", check_comma_cnt("double,double"));
// 	return (0);
// }
