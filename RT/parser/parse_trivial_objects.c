/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_trivial_objects.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liza <liza@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 11:26:10 by liza              #+#    #+#             */
/*   Updated: 2019/02/21 12:55:49 by liza             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_private.h"

bool	parse_sphere(struct s_obj_js fields, struct s_scene *scene)
{
	struct s_obj *object;

	if (!fields.position || !fields.radius)
		return (false);
	object = ft_memalloc(sizeof(struct s_obj));
	object->type = SPHERE;
	parse_vec3(fields.position, &object->primitive.s.position);
	object->primitive.s.r2 = fields.radius->valuedouble *
							fields.radius->valuedouble;
	parse_common_obj_values(fields, object);
	if (!IN_RANGE(object->primitive.s.r2, 0.0f, INFINITY))
	{
		ft_memdel((void**)&object);
		ft_putendl("Invalid radius for sphere");
		return (false);
	}
	ft_lst_push_front(&scene->primitives, object);
	return (true);
}

bool	parse_plane(struct s_obj_js fields, struct s_scene *scene)
{
	struct s_obj *object;

	if (!fields.position || !fields.normal)
		return (false);
	object = ft_memalloc(sizeof(struct s_obj));
	object->type = PLANE;
	parse_vec3(fields.position, &object->primitive.pl.position);
	parse_vec3(fields.normal, &object->primitive.pl.normal);
	parse_common_obj_values(fields, object);
	if (!NON_ZERO_VEC3(object->primitive.pl.normal))
	{
		ft_memdel((void**)&object);
		ft_putendl("Invalid normal for plane: zero vector");
		return (false);
	}
	object->primitive.pl.normal =
					normalize_float3(object->primitive.pl.normal);
	ft_lst_push_front(&scene->primitives, object);
	return (true);
}

bool	parse_cone(struct s_obj_js fields, struct s_scene *scene)
{
	struct s_obj *object;

	if (!fields.position || !fields.axis || !fields.angle)
		return (false);
	object = ft_memalloc(sizeof(struct s_obj));
	object->type = CONE;
	parse_vec3(fields.position, &object->primitive.cone.position);
	parse_vec3(fields.axis, &object->primitive.cone.axis);
	object->primitive.cone.angle = RAD(fields.angle->valuedouble);
	parse_common_obj_values(fields, object);
	object->primitive.cone.h = fields.height ? fields.height->valuedouble :
																		1e20f;
	if (!NON_ZERO_VEC3(object->primitive.cone.axis) ||
		!IN_RANGE(object->primitive.cone.h, 0.0f, 1e20f) ||
		!IN_RANGE(object->primitive.cone.angle, 0.0f, M_PI))
	{
		ft_memdel((void**)&object);
		ft_putendl("Invalid parametrs for cone");
		return (false);
	}
	object->primitive.cone.axis = normalize_float3(object->primitive.cone.axis);
	ft_lst_push_front(&scene->primitives, object);
	return (true);
}

bool	parse_cylinder(struct s_obj_js fields, struct s_scene *scene)
{
	struct s_obj *object;

	if (!fields.position || !fields.axis || !fields.radius)
		return (false);
	object = ft_memalloc(sizeof(struct s_obj));
	object->type = CYLINDER;
	parse_vec3(fields.position, &object->primitive.cyl.position);
	parse_vec3(fields.axis, &object->primitive.cyl.axis);
	object->primitive.cyl.r = fields.radius->valuedouble;
	parse_common_obj_values(fields, object);
	object->primitive.cyl.h = fields.height ? fields.height->valuedouble :
																		1e20f;
	if (!NON_ZERO_VEC3(object->primitive.cone.axis) ||
		!IN_RANGE(object->primitive.cyl.h, 0.0f, 1e20f) ||
		!IN_RANGE(object->primitive.cyl.r, 0.0f, 1e20f))
	{
		ft_memdel((void**)&object);
		ft_putstr("Invalid parametrs for cylinder");
		return (false);
	}
	object->primitive.cyl.axis = normalize_float3(object->primitive.cyl.axis);
	ft_lst_push_front(&scene->primitives, object);
	return (true);
}

bool	parse_disk(struct s_obj_js fields, struct s_scene *scene)
{
	struct s_obj *object;

	if (!fields.normal || !fields.radius || !fields.position)
		return (false);
	object = ft_memalloc(sizeof(struct s_obj));
	object->type = DISK;
	parse_vec3(fields.position, &object->primitive.disk.position);
	parse_vec3(fields.normal, &object->primitive.disk.normal);
	object->primitive.disk.r = fields.radius->valuedouble;
	parse_common_obj_values(fields, object);
	if (!NON_ZERO_VEC3(object->primitive.disk.normal) ||
		!IN_RANGE(object->primitive.disk.r, 0.0f, INFINITY))
	{
		ft_memdel((void**)&object);
		ft_putstr("Invalid parametrs for dsik");
		return (false);
	}
	object->primitive.disk.normal =
							normalize_float3(object->primitive.disk.normal);
	ft_lst_push_front(&scene->primitives, object);
	return (true);
}
