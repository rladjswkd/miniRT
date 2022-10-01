/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 23:49:29 by gyepark           #+#    #+#             */
/*   Updated: 2021/12/05 22:00:55 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
int	find_new_line(char *data, int start, int len)
{
	int	i;

	i = start;
	while (i < start + len && data[i] != '\n')
		i++;
	if (i == start + len)
		return (-1);
	return (i);
}

char	*concat_data(char *d1, char *d2, int len_d1, int len_d2)
{
	char	*concatenated;
	int		i_d1;
	int		i_d2;

	concatenated = (char *)malloc(sizeof(char) * (len_d1 + len_d2));
	if (!concatenated)
		return (0);
	i_d1 = -1;
	while (++i_d1 < len_d1)
		concatenated[i_d1] = d1[i_d1];
	i_d2 = 0;
	while (i_d2 < len_d2)
		concatenated[i_d1++] = d2[i_d2++];
	free(d1);
	return (concatenated);
}

void	copy_data(char *dst, char *src, int dstsize, int is_string)
{
	int	i;

	i = -1;
	while (++i + is_string < dstsize)
		dst[i] = src[i];
	if (is_string)
		dst[i] = '\0';
}

char	*get_part(char *d, unsigned int start, int len_part, int is_string)
{
	char	*output;

	output = (char *)malloc(sizeof(char) * (len_part + is_string));
	if (!output)
		return (0);
	copy_data(output, d + start, len_part + is_string, is_string);
	return (output);
}
