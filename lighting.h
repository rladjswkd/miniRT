/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 19:58:47 by gyepark           #+#    #+#             */
/*   Updated: 2022/11/11 19:58:47 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHTING_H
# define LIGHTING_H
# include "structure.h"

t_vec	compute_diffuse(t_vec inter, t_vec n, t_light light);
t_vec	compute_specular(t_vec inter, t_vec n, t_vec v, t_light light);
t_vec	compute_lighting(t_vec inter, t_vec n, t_vec v, t_world world);
#endif
