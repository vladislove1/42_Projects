/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liza <liza@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 10:13:47 by liza              #+#    #+#             */
/*   Updated: 2019/02/21 13:09:42 by liza             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_private.h"

static bool		parse_objects(cJSON *root, struct s_scene *scene)
{
	cJSON	*objects;
	int		index;
	int		parsed_objects_num;

	objects = cJSON_GetObjectItem(root, "objects");
	index = -1;
	if (!cJSON_IsArray(objects) ||
		!(scene->num_objects = cJSON_GetArraySize(objects)))
	{
		ft_putendl("Invalid array of objects");
		return (false);
	}
	parsed_objects_num = scene->num_objects;
	while (++index < parsed_objects_num)
	{
		if (!parse_obj(cJSON_GetArrayItem(objects, index), scene))
		{
			ft_putendl("Invalid input for object");
			return (false);
		}
	}
	return (true);
}

static bool		parse_lights(cJSON *root, struct s_scene *scene)
{
	cJSON			*lights;

	lights = cJSON_GetObjectItem(root, "lights");
	if (lights == NULL)
	{
		scene->num_lights = 0;
		return (true);
	}
	else if (cJSON_IsArray(lights))
		scene->num_lights = cJSON_GetArraySize(lights);
	else
	{
		ft_putendl("Invalid array of lights");
		return (false);
	}
	return (init_lights(lights, scene));
}

bool			init_camera(struct s_scene *scene)
{
	scene->camera.direction = (cl_float3){{0.0f, 0.0f, 1.0f, 0.0f}};
	scene->camera.position = (cl_float3){{0.0f, 0.0f, -5.0f, 0.0f}};
	scene->camera.right = (cl_float3){{1.0f, 0.0f, 0.0f, 0.0f}};
	scene->camera.up = (cl_float3){{0.0f, 1.0f, 0.0f, 0.0f}};
	return (true);
}

static bool		parse_cameras(cJSON *root, struct s_scene *scene)
{
	cJSON			*cameras;
	bool			valid;

	cameras = cJSON_GetObjectItem(root, "cameras");
	if (cameras == NULL)
		return (init_camera(scene));
	else if (!(cJSON_IsArray(cameras)) ||
			!(scene->num_cameras = cJSON_GetArraySize(cameras)))
	{
		ft_putendl("Invalid array of cameras");
		return (false);
	}
	valid = parse_camera(cJSON_GetArrayItem(cameras, 0), &scene->camera);
	if (scene->num_cameras > 1)
		valid = valid &&
				parse_camera(cJSON_GetArrayItem(cameras, 0), &scene->left_eye);
	else
		scene->left_eye = scene->camera;
	if (!valid)
	{
		ft_putendl("Invalid input for cameras");
		return (false);
	}
	scene->default_camera = scene->camera;
	return (true);
}

struct s_scene	*parse_scene(char *path)
{
	char			*file;
	struct s_scene	*scene;
	cJSON			*root;

	if (is_directory(path) || !read_file(path, &file))
		return (NULL);
	if (!(root = cJSON_Parse(file)))
	{
		ft_putendl(cJSON_GetErrorPtr());
		free(file);
		return (NULL);
	}
	free(file);
	scene = ft_memalloc(sizeof(*scene));
	if (!parse_objects(root, scene) || !parse_lights(root, scene) ||
		!parse_cameras(root, scene))
		ft_memdel((void**)&scene);
	cJSON_Delete(root);
	return (scene);
}
