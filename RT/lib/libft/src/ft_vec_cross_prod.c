/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec_cross_prod.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvikhrov <yvikhrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/05 13:13:58 by yvikhrov          #+#    #+#             */
/*   Updated: 2018/07/15 18:23:52 by yvikhrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <math.h>

t_vec3	vec3_cross(t_vec3 vec1, t_vec3 vec2)
{
	return ((t_vec3){vec1.y * vec2.z - vec1.z * vec2.y,
		vec1.z * vec2.x - vec1.x * vec2.z,
		vec1.x * vec2.y - vec1.y * vec2.x});
}

t_vec3	vec3_normalize(t_vec3 vec)
{
	float	inv_length;

	inv_length = 1.0f / sqrt(vec3_dot(vec, vec));
	return ((t_vec3){vec.x * inv_length, vec.y * inv_length,
										vec.z * inv_length});
}

float	vec3_length(t_vec3 vec)
{
	return (sqrtf(vec3_dot(vec, vec)));
}
