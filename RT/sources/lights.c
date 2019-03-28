/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liza <liza@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 13:43:36 by liza              #+#    #+#             */
/*   Updated: 2019/02/02 23:39:01 by liza             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

struct s_light			*init_lights_array(struct s_list *light, int num_lights)
{
	struct s_list		*head;
	struct s_light		*lights;
	int					i;

	lights = (struct s_light*)malloc(sizeof(struct s_light) * num_lights);
	if (!lights)
		return (NULL);
	head = light;
	i = 0;
	while (head)
	{
		lights[i] = *(struct s_light*)head->content;
		i++;
		head = head->next;
	}
	return (lights);
}

bool					update_lights_buffers(t_app *app)
{
	struct s_light		*lights;

	if (app->cl.lights)
		cl_buffer_release(app->cl.lights);
	lights = init_lights_array(app->scene->lights, app->scene->num_lights);
	app->cl.lights = cl_buffer_init(app->cl.cl, sizeof(struct s_light) *
		app->scene->num_lights + 1, lights);
	free(lights);
	return (app->cl.lights != NULL);
}

void					remove_light(t_app *app, int light_index)
{
	t_list				*head;
	t_list				*previous;
	int					i;

	head = app->scene->lights;
	i = 0;
	while (head && light_index--)
	{
		previous = head;
		head = head->next;
	}
	if (head)
	{
		free(head->content);
		if (head == app->scene->lights)
			app->scene->lights = head->next;
		else
			previous->next = head->next;
		free(head);
		app->scene->num_lights--;
		update_lights_buffers(app);
	}
}

int						count_implicit_objects_num(struct s_list *head)
{
	int					n;
	int					type;

	n = 0;
	while (head)
	{
		type = ((struct s_obj*)head->content)->type;
		if (type == CONE)
			n += 1;
		else if (type == CYLINDER)
			n += 2;
		head = head->next;
	}
	return (n);
}
