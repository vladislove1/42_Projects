/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvikhrov <yvikhrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 21:51:29 by yvikhrov          #+#    #+#             */
/*   Updated: 2018/07/15 18:16:57 by yvikhrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <math.h>

t_vec3	vec3_add(t_vec3 vec1, t_vec3 vec2)
{
	return ((t_vec3){vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z});
}

t_vec3	vec3_sub(t_vec3 vec1, t_vec3 vec2)
{
	return ((t_vec3){vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z});
}

t_vec3	vec3_mult_scalar(t_vec3 vec, float scalar)
{
	return ((t_vec3){vec.x * scalar, vec.y * scalar, vec.z * scalar});
}

t_vec3	vec3_mult_vec3(t_vec3 vec1, t_vec3 vec2)
{
	return ((t_vec3){vec1.x * vec2.x, vec1.y * vec2.y, vec1.z * vec2.z});
}

t_vec3	vec3_rotate_2d(t_vec3 vec, float angle)
{
	return (vec3_init(cos(angle) * vec.x - sin(angle) * vec.y,
					cos(angle) * vec.y + sin(angle) * vec.x, 0.0f));
}
