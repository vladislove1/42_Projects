/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liza <liza@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 10:53:40 by liza              #+#    #+#             */
/*   Updated: 2019/02/21 12:47:18 by liza             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_private.h"

bool			parse_light_sphere(struct s_obj_js fields, struct s_light *l)
{
	if (!fields.position)
		return (false);
	l->type = SPHERE;
	parse_vec3(fields.position, &l->primitive.s.position);
	l->primitive.s.r2 = 1.0f;
	return (true);
}

bool			parse_light_plane(struct s_obj_js fields, struct s_light *light)
{
	if (!fields.position || !fields.normal)
		return (false);
	light->type = PLANE;
	parse_vec3(fields.position, &light->primitive.pl.position);
	parse_vec3(fields.normal, &light->primitive.pl.normal);
	if (!NON_ZERO_VEC3(light->primitive.pl.normal))
	{
		ft_putendl("Invalid normal for light plane: zero vector");
		return (false);
	}
	return (true);
}

bool			parse_light_cone(struct s_obj_js fields, struct s_light *light)
{
	if (!fields.position || !fields.axis || !fields.angle)
		return (false);
	light->type = CONE;
	parse_vec3(fields.position, &light->primitive.cone.position);
	parse_vec3(fields.axis, &light->primitive.cone.axis);
	light->primitive.cone.angle = RAD(fields.angle->valuedouble);
	light->primitive.cone.h = INFINITY;
	if (!NON_ZERO_VEC3(light->primitive.cone.axis) ||
		!IN_RANGE(light->primitive.cone.h, 0.0f, INFINITY) ||
		!IN_RANGE(light->primitive.cone.angle, 0.0f, M_PI))
	{
		ft_putendl("Invalid parametrs for light cone");
		return (false);
	}
	return (true);
}

void			parse_light_type(struct s_obj_js fields, struct s_light *light)
{
	char *type;

	type = cJSON_GetStringValue(fields.type);
	if (!ft_strcmp(type, "sphere"))
	{
		if (!parse_light_sphere(fields, light))
			ft_memdel((void**)&light);
	}
	else if (!ft_strcmp(type, "plane"))
	{
		if (!parse_light_plane(fields, light))
			ft_memdel((void**)&light);
	}
	else if (!ft_strcmp(type, "cone"))
	{
		if (!parse_light_cone(fields, light))
			ft_memdel((void**)&light);
	}
	else
	{
		ft_putendl("Invalid light type");
		ft_memdel((void**)&light);
	}
}

struct s_light	*parse_light(cJSON *js)
{
	struct s_obj_js	fields;
	struct s_light	*light;

	fields = parse_common_fields(js);
	light = ft_memalloc(sizeof(struct s_light));
	if (!fields.type || !cJSON_IsString(fields.type))
	{
		ft_putstr("Parameter 'type' for light doesn't exist. ");
		ft_putendl("Default type = sphere.");
		light->type = SPHERE;
	}
	else
		parse_light_type(fields, light);
	if (!light)
		return (NULL);
	if (!fields.intensity)
	{
		ft_putstr("Parameter 'intensity' for light doesn't exist. ");
		ft_putendl("Default value = 1.0f.");
		light->intensity = 1.0f;
	}
	else
		light->intensity = fields.intensity->valuedouble;
	return (light);
}
