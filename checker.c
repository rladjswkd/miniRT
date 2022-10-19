/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_identifier.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgim <cgim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 21:47:41 by cgim              #+#    #+#             */
/*   Updated: 2022/09/29 21:50:37 by cgim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "string_utils.h"

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

	// if (type == 0)
	// 	return (-1);
	// if (ft_strncmp("A", type, n) == 0)
	// 	return (0);
	// else if (ft_strncmp("C", type, n) == 0)
	// 	return (1);
	// else if (ft_strncmp("L", type, n) == 0)
	// 	return (2);
	// else if (ft_strncmp("sp", type, n) == 0)
	// 	return (3);
	// else if (ft_strncmp("pl", type, n) == 0)
	// 	return (4);
	// else if (ft_strncmp("cy", type, n) == 0)
	// 	return (5);
	// return (-1);
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
