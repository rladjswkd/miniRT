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

#include "parser.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = -1;
	while (++i < n && (s1[i] || s2[i]))
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	return (0);
}

int	check_identifier(char *type)
{
	size_t	n;

	n = ft_strlen(type);
	if (type == 0)
		return (-1);
	if (ft_strncmp("A", type, n) == 0)
		return (0);
	else if (ft_strncmp("C", type, n) == 0)
		return (1);
	else if (ft_strncmp("L", type, n) == 0)
		return (2);
	else if (ft_strncmp("sp", type, n) == 0)
		return (3);
	else if (ft_strncmp("pl", type, n) == 0)
		return (4);
	else if (ft_strncmp("cy", type, n) == 0)
		return (5);
	return (-1);
}
