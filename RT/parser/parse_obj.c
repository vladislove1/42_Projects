/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liza <liza@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 11:43:38 by liza              #+#    #+#             */
/*   Updated: 2019/02/21 12:42:37 by liza             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_private.h"

struct s_obj_js	parse_common_fields(cJSON *js)
{
	struct s_obj_js fields;

	GET_ITEM(type);
	GET_ITEM(color);
	GET_ITEM(position);
	GET_ITEM(normal);
	GET_ITEM(height);
	GET_ITEM(radius);
	GET_ITEM(axis);
	GET_ITEM(angle);
	GET_ITEM(big_radius);
	GET_ITEM(width);
	GET_ITEM(axis_2);
	GET_ITEM(color_2);
	GET_ITEM(procedure);
	GET_ITEM(ambient);
	GET_ITEM(reflection);
	GET_ITEM(transparent);
	GET_ITEM(intensity);
	GET_ITEM(refraction);
	GET_ITEM(specular);
	GET_ITEM(point_1);
	GET_ITEM(point_2);
	GET_ITEM(point_3);
	return (fields);
}

bool			parse_trivial_objects(struct s_obj_js fields, char *type,
														struct s_scene *scene)
{
	if (!ft_strcmp(type, "sphere"))
		return (parse_sphere(fields, scene));
	else if (!ft_strcmp(type, "plane"))
		return (parse_plane(fields, scene));
	else if (!ft_strcmp(type, "cone"))
		return (parse_cone(fields, scene));
	else if (!ft_strcmp(type, "cylinder"))
		return (parse_cylinder(fields, scene));
	else if (!ft_strcmp(type, "disk"))
		return (parse_disk(fields, scene));
	return (false);
}

bool			parse_obj(cJSON *js, struct s_scene *scene)
{
	struct s_obj_js	fields;
	struct s_obj	*object;
	char			*type;

	fields = parse_common_fields(js);
	object = NULL;
	if (cJSON_IsString(fields.type))
	{
		type = cJSON_GetStringValue(fields.type);
		if (!ft_strcmp(type, "parabola"))
			return (parse_parabola(fields, scene));
		else if (!ft_strcmp(type, "ellipsoid"))
			return (parse_ellipsoid(fields, scene));
		else if (!ft_strcmp(type, "triangle"))
			return (parse_triangle(fields, scene));
		else if (!ft_strcmp(type, "torus"))
			return (parse_torus(fields, scene));
		else if (!ft_strcmp(type, "mobius"))
			return (parse_mobius(fields, scene));
		else
			return (parse_trivial_objects(fields, type, scene));
	}
	return (false);
}
