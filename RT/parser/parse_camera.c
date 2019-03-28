/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liza <liza@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 10:55:27 by liza              #+#    #+#             */
/*   Updated: 2019/02/21 12:40:00 by liza             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_private.h"

static struct s_camera_js	get_camera_fields(cJSON *js)
{
	struct s_camera_js fields;

	GET_ITEM(position);
	GET_ITEM(up);
	GET_ITEM(poi);
	return (fields);
}

bool						parse_camera(cJSON *js, struct s_camera *camera)
{
	struct s_camera_js fields;

	fields = get_camera_fields(js);
	if (!fields.position)
		return (false);
	parse_vec3(fields.position, &camera->position);
	parse_vec3(fields.poi, &camera->direction);
	parse_vec3(fields.up, &camera->up);
	TO_VEC3(camera->direction) = vec3_sub(TO_VEC3(camera->direction),
										TO_VEC3(camera->position));
	TO_VEC3(camera->right) = vec3_cross(TO_VEC3(camera->up),
										TO_VEC3(camera->direction));
	if (!NON_ZERO_VEC3(camera->direction) ||
		!NON_ZERO_VEC3(camera->right) ||
		!NON_ZERO_VEC3(camera->up))
	{
		ft_putendl("Invalid parameters for camera");
		return (false);
	}
	TO_VEC3(camera->direction) = vec3_normalize(TO_VEC3(camera->direction));
	TO_VEC3(camera->up) = vec3_normalize(TO_VEC3(camera->up));
	TO_VEC3(camera->right) = vec3_normalize(TO_VEC3(camera->right));
	return (true);
}
