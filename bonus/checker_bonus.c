/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgim <cgim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 21:47:41 by cgim              #+#    #+#             */
/*   Updated: 2022/11/11 19:55:15 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structure_bonus.h"
#include "string_utils_bonus.h"
#include <math.h>

int	check_identifier(char *type)
{
	size_t	n;
	int		ret;

	if (!type || !(*type))
		return (-1);
	n = ft_strlen(type);
	ret = !ft_strncmp("A", type, n) * 1
		+ !ft_strncmp("C", type, n) * 2
		+ !ft_strncmp("L", type, n) * 3
		+ !ft_strncmp("sp", type, n) * 4
		+ !ft_strncmp("pl", type, n) * 5
		+ !ft_strncmp("cy", type, n) * 6
		+ !ft_strncmp("cn", type, n) * 7;
	return (ret - 1);
}

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
		&& fabs(sqrt(x * x + y * y + z * z) - 1) < 1e-6);
}
