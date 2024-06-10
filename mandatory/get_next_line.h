/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 23:49:34 by gyepark           #+#    #+#             */
/*   Updated: 2021/12/07 20:07:24 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>

typedef struct s_builder
{
	char	*data;
	int		len;
	int		index;
}	t_builder;
char	*get_next_line(int fd);
int		find_new_line(char *data, int start, int len);
char	*concat_data(char *d1, char *d2, int len_d1, int len_d2);
void	copy_data(char *dst, char *src, int len_dst, int is_string);
char	*get_part(char *d, unsigned int start, int dstsize, int is_string);
#endif
