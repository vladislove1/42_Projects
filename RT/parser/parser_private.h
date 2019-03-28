/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_private.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liza <liza@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 23:29:45 by liza              #+#    #+#             */
/*   Updated: 2019/02/05 09:58:29 by liza             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_PRIVATE_H
# define PARSER_PRIVATE_H

# include "rt.h"
# include <cJSON.h>

# define GET_ITEM(name) fields.name = cJSON_GetObjectItem(js, #name)
# define NON_ZERO_VEC3(vec) (vec.x != 0.0f || vec.y != 0.0f || vec.z != 0.0f)
# define IN_RANGE(num, min, max) (num >= min && num <= max)
# define RAD(arg) M_PI * arg / 180.0f

struct			s_obj_js
{
	cJSON *type;
	cJSON *color;
	cJSON *position;
	cJSON *normal;
	cJSON *height;
	cJSON *radius;
	cJSON *axis;
	cJSON *angle;
	cJSON *big_radius;
	cJSON *width;
	cJSON *axis_2;
	cJSON *color_2;
	cJSON *procedure;
	cJSON *ambient;
	cJSON *reflection;
	cJSON *transparent;
	cJSON *intensity;
	cJSON *refraction;
	cJSON *specular;
	cJSON *point_1;
	cJSON *point_2;
	cJSON *point_3;
};

struct			s_light_js
{
	cJSON *type;
	cJSON *position;
	cJSON *intensity;
};

struct			s_camera_js
{
	cJSON *position;
	cJSON *up;
	cJSON *poi;
};

bool			parse_obj(cJSON *js, struct s_scene *scene);
struct s_light	*parse_light(cJSON *js);
bool			parse_camera(cJSON *js, struct s_camera *camera);
bool			parse_vec3(cJSON *js, cl_float3 *vec);
bool			parse_color(cJSON *js, cl_float3 *color);
bool			init_lights(cJSON *lights, struct s_scene *scene);

bool			vec3_in_range(cl_float3 vec, float min, float max);
cl_float3		normalize_float3(cl_float3 vec);
void			parse_procedure(struct s_obj_js fields, struct s_obj *object);
void			parse_common_obj_values(struct s_obj_js f, struct s_obj *obj);

bool			parse_cylinder(struct s_obj_js fields, struct s_scene *scene);
bool			parse_sphere(struct s_obj_js fields, struct s_scene *scene);
bool			parse_plane(struct s_obj_js fields, struct s_scene *scene);
bool			parse_cone(struct s_obj_js fields, struct s_scene *scene);
bool			parse_disk(struct s_obj_js fields, struct s_scene *scene);

bool			parse_parabola(struct s_obj_js fields, struct s_scene *scene);
bool			parse_ellipsoid(struct s_obj_js fields, struct s_scene *scene);
bool			parse_triangle(struct s_obj_js fields, struct s_scene *scene);
bool			parse_mobius(struct s_obj_js fields, struct s_scene *scene);
bool			parse_torus(struct s_obj_js fields, struct s_scene *scene);

struct s_obj_js	parse_common_fields(cJSON *js);

#endif
