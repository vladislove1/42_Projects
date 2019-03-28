/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liza <liza@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 11:15:26 by liza              #+#    #+#             */
/*   Updated: 2019/02/21 13:08:18 by liza             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_private.h"

bool		vec3_in_range(cl_float3 vec, float min, float max)
{
	if (!IN_RANGE(vec.x, min, max) || !IN_RANGE(vec.y, min, max) ||
		!IN_RANGE(vec.z, min, max))
		return (false);
	return (true);
}

cl_float3	normalize_float3(cl_float3 vec)
{
	t_vec3 normal;

	normal = TO_VEC3(vec);
	normal = vec3_normalize(normal);
	return ((cl_float3){{normal.x, normal.y, normal.z}});
}

void		parse_procedure(struct s_obj_js fields, struct s_obj *object)
{
	char *type;

	if (cJSON_IsString(fields.procedure))
	{
		type = cJSON_GetStringValue(fields.procedure);
		if (!ft_strcmp(type, "default"))
			object->proced = DEFAULT;
		if (!ft_strcmp(type, "brick"))
			object->proced = BRICK;
		if (!ft_strcmp(type, "checkerboard"))
			object->proced = CHECKERBOARD;
		if (!ft_strcmp(type, "perlin"))
			object->proced = PERLIN;
		if (!ft_strcmp(type, "normal disruption"))
			object->proced = NORMAL_DISRUP;
		if (!ft_strcmp(type, "grid"))
			object->proced = GRID;
		if (!ft_strcmp(type, "texture_1"))
			object->proced = TEXTURE_1;
		if (!ft_strcmp(type, "texture_2"))
			object->proced = TEXTURE_2;
		if (!ft_strcmp(type, "texture_3"))
			object->proced = TEXTURE_3;
	}
}

void		parse_common_obj_values(struct s_obj_js fields,
														struct s_obj *object)
{
	if (!parse_color(fields.color, &object->color))
	{
		ft_putendl("Parameter 'color' doesn't exist. Default color - white.");
		object->color = (cl_float3){{1.0f, 1.0f, 1.0f}};
	}
	if (fields.color_2)
		parse_color(fields.color_2, &object->color2);
	if (fields.ambient)
		object->ambient = fields.ambient->valuedouble;
	if (fields.transparent)
		object->transparency = fields.transparent->valuedouble;
	if (fields.reflection)
		object->reflect = fields.reflection->valuedouble;
	if (fields.refraction)
		object->refract = fields.refraction->valuedouble;
	if (fields.procedure)
		parse_procedure(fields, object);
	if (fields.specular)
		object->specular = fields.specular->valueint;
	object->scale = 1.0f;
	object->horiz_shift = 0.0f;
	object->vertic_shift = 0.0f;
}

bool		init_lights(cJSON *lights, struct s_scene *scene)
{
	int				index;
	struct s_light	*light;

	index = -1;
	while (++index < scene->num_lights)
	{
		if (!(light = parse_light(cJSON_GetArrayItem(lights, index))))
		{
			ft_putendl("Invalid input for light");
			return (false);
		}
		ft_lst_push_front(&scene->lights, light);
	}
	return (true);
}
