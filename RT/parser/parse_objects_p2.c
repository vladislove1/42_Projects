/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects_p2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liza <liza@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 11:34:40 by liza              #+#    #+#             */
/*   Updated: 2019/02/21 12:55:25 by liza             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_private.h"

bool	parse_parabola(struct s_obj_js fields, struct s_scene *scene)
{
	struct s_obj *object;

	if (!fields.axis || !fields.radius || !fields.position)
		return (false);
	object = ft_memalloc(sizeof(struct s_obj));
	object->type = PARABOLA;
	parse_vec3(fields.position, &object->primitive.parab.position);
	parse_vec3(fields.axis, &object->primitive.parab.axis);
	object->primitive.parab.a = fields.radius->valuedouble;
	parse_common_obj_values(fields, object);
	if (!NON_ZERO_VEC3(object->primitive.parab.axis) ||
		!IN_RANGE(object->primitive.parab.a, 0.0f, INFINITY))
	{
		ft_memdel((void**)&object);
		ft_putstr("Invalid parametrs for paraboloid");
		return (false);
	}
	object->primitive.parab.axis =
								normalize_float3(object->primitive.parab.axis);
	ft_lst_push_front(&scene->primitives, object);
	return (true);
}

bool	parse_ellipsoid(struct s_obj_js fields, struct s_scene *scene)
{
	struct s_obj *object;

	if (!fields.axis || !fields.radius || !fields.position ||
		!fields.big_radius)
		return (false);
	object = ft_memalloc(sizeof(struct s_obj));
	object->type = ELLIPSOID;
	parse_vec3(fields.position, &object->primitive.ellips.position);
	parse_vec3(fields.axis, &object->primitive.ellips.axis);
	object->primitive.ellips.r = fields.radius->valuedouble;
	object->primitive.ellips.a = fields.big_radius->valuedouble;
	parse_common_obj_values(fields, object);
	if (!NON_ZERO_VEC3(object->primitive.ellips.axis) ||
		!IN_RANGE(object->primitive.ellips.a, 0.0f, INFINITY) ||
		!IN_RANGE(object->primitive.ellips.r, 0.0f, INFINITY))
	{
		ft_memdel((void**)&object);
		ft_putstr("Invalid parametrs for ellipsoid");
		return (false);
	}
	object->primitive.ellips.axis =
							normalize_float3(object->primitive.ellips.axis);
	ft_lst_push_front(&scene->primitives, object);
	return (true);
}

bool	parse_triangle(struct s_obj_js fields, struct s_scene *scene)
{
	struct s_obj *object;

	if (!fields.point_1 || !fields.point_2 || !fields.point_3)
		return (false);
	object = ft_memalloc(sizeof(struct s_obj));
	object->type = TRIANGLE;
	parse_vec3(fields.point_1, &object->primitive.triangle.point_a);
	parse_vec3(fields.point_2, &object->primitive.triangle.point_b);
	parse_vec3(fields.point_3, &object->primitive.triangle.point_c);
	parse_common_obj_values(fields, object);
	ft_lst_push_front(&scene->primitives, object);
	return (true);
}

bool	parse_mobius(struct s_obj_js fields, struct s_scene *scene)
{
	struct s_obj *object;

	if (!fields.axis || !fields.axis_2 || !fields.radius || !fields.position
		|| !fields.width)
		return (NULL);
	object = ft_memalloc(sizeof(struct s_obj));
	object->type = MOBIUS;
	parse_vec3(fields.position, &object->primitive.mobius.position);
	parse_vec3(fields.axis, &object->primitive.mobius.axis_x);
	parse_vec3(fields.axis_2, &object->primitive.mobius.axis_y);
	object->primitive.mobius.r = fields.radius->valuedouble;
	object->primitive.mobius.a = fields.width->valuedouble;
	parse_common_obj_values(fields, object);
	if (!NON_ZERO_VEC3(object->primitive.mobius.axis_x) ||
		!NON_ZERO_VEC3(object->primitive.mobius.axis_y) ||
		!IN_RANGE(object->primitive.mobius.r, 0.0f, INFINITY) ||
		!IN_RANGE(object->primitive.mobius.a, 0.0f, INFINITY))
	{
		ft_memdel((void**)&object);
		ft_putstr("Invalid parametrs for mobius");
		return (false);
	}
	ft_lst_push_front(&scene->primitives, object);
	return (true);
}

bool	parse_torus(struct s_obj_js fields, struct s_scene *scene)
{
	struct s_obj *object;

	if (!fields.axis || !fields.big_radius || !fields.radius ||
		!fields.position)
		return (NULL);
	object = ft_memalloc(sizeof(struct s_obj));
	object->type = TORUS;
	parse_vec3(fields.position, &object->primitive.torus.position);
	parse_vec3(fields.axis, &object->primitive.torus.axis);
	object->primitive.torus.r_1 = fields.radius->valuedouble;
	object->primitive.torus.r_2 = fields.big_radius->valuedouble;
	parse_common_obj_values(fields, object);
	if (!NON_ZERO_VEC3(object->primitive.torus.axis) ||
		!IN_RANGE(object->primitive.torus.r_1, 0.0f, INFINITY) ||
		!IN_RANGE(object->primitive.torus.r_2, 0.0f, INFINITY))
	{
		ft_memdel((void**)&object);
		ft_putstr("Invalid parametrs for torus");
		return (false);
	}
	ft_lst_push_front(&scene->primitives, object);
	return (true);
}
