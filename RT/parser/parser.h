/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liza <liza@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 23:29:30 by liza              #+#    #+#             */
/*   Updated: 2018/12/27 22:56:12 by liza             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "cl/cl.h"
# include "libft.h"

# define TO_VEC3(arg) (*(t_vec3*)&arg)

typedef struct			s_camera
{
	cl_float3			direction;
	cl_float3			right;
	cl_float3			up;
	cl_float3			position;
	bool				initialized;
}						t_camera;

typedef enum			e_prim_type
{
	SPHERE = 0,
	PLANE,
	CONE,
	CYLINDER,
	DISK,
	MOBIUS,
	TORUS,
	TRIANGLE,
	PARABOLA,
	ELLIPSOID,
	PRIMITIVE_TYPES_AMOUNT
}						t_prim_type;

typedef enum			e_procedural_type
{
	DEFAULT = 0,
	CHECKERBOARD,
	GRID,
	BRICK,
	PERLIN,
	NORMAL_DISRUP,
	TEXTURE_1,
	TEXTURE_2,
	TEXTURE_3,
	PROCEDURE_NUM
}						t_procedural_type;

struct					s_sphere
{
	cl_float3			position;
	cl_float			r2;
};

struct					s_plane
{
	cl_float3			position;
	cl_float3			normal;
};

struct					s_cylinder
{
	cl_float3			position;
	cl_float3			axis;
	cl_float			r;
	cl_float			h;
};

struct					s_cone
{
	cl_float3			position;
	cl_float3			axis;
	cl_float			angle;
	cl_float			h;
};

struct					s_disk
{
	cl_float3			position;
	cl_float3			normal;
	cl_float			r;
};

struct					s_torus
{
	cl_float3			position;
	cl_float3			axis;
	cl_float			r_1;
	cl_float			r_2;
};

struct					s_mobius
{
	cl_float3			position;
	cl_float3			axis_x;
	cl_float3			axis_y;
	cl_float			r;
	cl_float			a;
};

struct					s_triangle
{
	cl_float4			point_a;
	cl_float4			point_b;
	cl_float4			point_c;

};

struct					s_parabola
{
	cl_float3			position;
	cl_float3			axis;
	cl_float			a;

};

struct					s_ellipsoid
{
	cl_float3			position;
	cl_float3			axis;
	cl_float			r;
	cl_float			a;
};

typedef union			u_primitive
{
	struct s_plane		pl;
	struct s_sphere		s;
	struct s_cylinder	cyl;
	struct s_cone		cone;
	struct s_disk		disk;
	struct s_torus		torus;
	struct s_mobius		mobius;
	struct s_parabola	parab;
	struct s_ellipsoid	ellips;
	struct s_triangle	triangle;
	cl_float3			position;
}						t_primitive;

struct					s_obj
{
	t_primitive			primitive;
	cl_float4			color;
	cl_float4			color2;
	cl_float			ambient;
	cl_float			reflect;
	cl_float			transparency;
	cl_float			refract;
	cl_int				specular;
	cl_int				type;
	cl_int				proced;
	cl_float			scale;
	cl_float			horiz_shift;
	cl_float			vertic_shift;
};

struct					s_light
{
	t_primitive			primitive;
	cl_float			intensity;
	int					type;
};

struct					s_scene
{
	struct s_list		*primitives;
	struct s_list		*lights;
	int					num_objects;
	int					num_objects_to_render;
	int					num_lights;
	int					num_cameras;
	struct s_camera		camera;
	struct s_camera		default_camera;
	struct s_camera		left_eye;
};

struct s_scene			*parse_scene(char *path);

#endif
