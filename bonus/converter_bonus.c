/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 19:55:18 by gyepark           #+#    #+#             */
/*   Updated: 2022/11/11 19:55:19 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	get_sign(char **str)
{
	int	sign;

	sign = 1;
	if (**str == '-' || **str == '+')
		if (*((*str)++) == '-')
			sign = -1;
	return (sign);
}

int	get_double(char *str, double *converted)
{
	double	scale;
	int		sign;

	sign = get_sign(&str);
	*converted = 0;
	while (47 < *str && *str < 58)
		*converted = *converted * 10 + sign * (*(str++) - 48);
	if (*str != '.' && *str != '\0')
		return (0);
	if (*str == '\0')
		return (1);
	str++;
	scale = 10;
	while (47 < *str && *str < 58)
	{
		*converted += sign * (*(str++) - 48) / scale;
		scale *= 10;
	}
	if (*str != '\0')
		return (0);
	return (1);
}

int	get_int(char *str, int *converted)
{
	int	sign;
	int	ret;

	sign = get_sign(&str);
	ret = 0;
	while (47 < *str && *str < 58)
		ret = ret * 10 + sign * (*(str++) - 48);
	if (*str != '\0')
		return (0);
	*converted = ret;
	return (1);
}
