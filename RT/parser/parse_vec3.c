/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_vec3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liza <liza@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 11:49:45 by liza              #+#    #+#             */
/*   Updated: 2019/02/21 12:49:30 by liza             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_private.h"

static bool	parse_nd_vec(cJSON *js, int dimension, const char *fields[],
															float *result)
{
	cJSON		*vec_js;
	int			i;

	i = -1;
	while (++i < dimension)
	{
		if (!(vec_js = cJSON_GetObjectItem(js, fields[i])) ||
			!cJSON_IsNumber(vec_js))
			return (false);
		result[i] = vec_js->valuedouble;
	}
	return (true);
}

bool		parse_vec3(cJSON *js, cl_float3 *vec)
{
	const char	*fields[] = {"x", "y", "z"};

	return (parse_nd_vec(js, 3, fields, (float*)vec));
}

bool		parse_color(cJSON *js, cl_float3 *color)
{
	const char	*fields[] = {"r", "g", "b"};

	return (parse_nd_vec(js, 3, fields, (float*)color) &&
			vec3_in_range(*color, 0.0f, 1.0f));
}
