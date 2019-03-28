/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liza <liza@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 13:43:36 by liza              #+#    #+#             */
/*   Updated: 2019/02/02 23:39:01 by liza             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void				add_disk_to_cone(struct s_obj *cone)
{
	cl_float3		new_position;
	struct s_obj	*disk;

	TO_VEC3(new_position) = vec3_sub(TO_VEC3(cone->primitive.cone.position),
		vec3_mult_scalar(TO_VEC3(cone->primitive.cone.axis),
			cone->primitive.cone.h));
	disk = cone + 1;
	*disk = *cone;
	disk->type = DISK;
	disk->primitive.disk.normal = cone->primitive.cone.axis;
	disk->primitive.disk.position = new_position;
	disk->primitive.disk.r = cone->primitive.cone.h *
		tan(cone->primitive.cone.angle);
}

void				add_disk_to_cylinder(struct s_obj *cylinder)
{
	cl_float3		new_position;
	struct s_obj	*disk1;
	struct s_obj	*disk2;

	TO_VEC3(new_position) = vec3_sub(TO_VEC3(cylinder->primitive.cyl.position),
		vec3_mult_scalar(TO_VEC3(cylinder->primitive.cyl.axis),
			cylinder->primitive.cyl.h * 0.5f));
	disk1 = cylinder + 1;
	*disk1 = *cylinder;
	disk1->type = DISK;
	disk1->primitive.disk.normal = cylinder->primitive.cyl.axis;
	disk1->primitive.disk.position = new_position;
	disk1->primitive.disk.r = cylinder->primitive.cyl.r;
	TO_VEC3(new_position) = vec3_add(TO_VEC3(cylinder->primitive.cyl.position),
		vec3_mult_scalar(TO_VEC3(cylinder->primitive.cyl.axis),
			cylinder->primitive.cyl.h * 0.5f));
	disk2 = cylinder + 2;
	*disk2 = *cylinder;
	disk2->type = DISK;
	disk2->primitive.disk.normal = cylinder->primitive.disk.normal;
	disk2->primitive.disk.position = new_position;
	disk2->primitive.disk.r = cylinder->primitive.cyl.r;
}

struct s_obj		*init_objects_array(struct s_list *primitives,
															int *num_primitives)
{
	struct s_list	*head;
	struct s_obj	*objects;
	int				i;

	*num_primitives += count_implicit_objects_num(primitives);
	objects = ft_memalloc(sizeof(struct s_obj) * (*num_primitives));
	if (!objects)
		return (NULL);
	head = primitives;
	i = 0;
	while (head)
	{
		objects[i] = *(struct s_obj*)head->content;
		if (objects[i].type == CONE)
			add_disk_to_cone(&objects[i++]);
		if (objects[i].type == CYLINDER)
		{
			add_disk_to_cylinder(&objects[i]);
			i = i + 2;
		}
		i++;
		head = head->next;
	}
	return (objects);
}

bool				update_object_buffers(t_app *app)
{
	struct s_obj	*objects;

	if (app->cl.objects)
		cl_buffer_release(app->cl.objects);
	app->scene->num_objects_to_render = app->scene->num_objects;
	objects = init_objects_array(app->scene->primitives,
		&app->scene->num_objects_to_render);
	app->cl.objects = cl_buffer_init(app->cl.cl, sizeof(struct s_obj) *
		app->scene->num_objects_to_render, objects);
	free(objects);
	return (app->cl.objects != NULL);
}

void				remove_object(t_app *app, int object_index)
{
	t_list			*head;
	t_list			*previous;
	int				i;

	head = app->scene->primitives;
	i = 0;
	while (head && object_index--)
	{
		previous = head;
		head = head->next;
	}
	if (head)
	{
		free(head->content);
		if (head == app->scene->primitives)
			app->scene->primitives = head->next;
		else
			previous->next = head->next;
		free(head);
		app->scene->num_objects--;
		update_object_buffers(app);
	}
}
