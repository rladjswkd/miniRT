/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_pattern.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 19:59:16 by gyepark           #+#    #+#             */
/*   Updated: 2022/11/11 19:59:17 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_PATTERN_H
# define OBJECT_PATTERN_H
# include "structure.h"

char	uv_pattern_at(t_uv uv, int w, int h);
t_rgb	get_img_rgb(t_img img, t_uv uv);
t_vec	get_basis_vec(t_vec v);
#endif
