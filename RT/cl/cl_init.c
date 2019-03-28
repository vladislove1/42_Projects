/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liza <liza@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/07 20:59:30 by liza              #+#    #+#             */
/*   Updated: 2018/09/07 22:52:18 by liza             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "cl_private.h"
#include "libft.h"

static void	opencl_error(const char *errinfo, const void *p, size_t cb, void *u)
{
	(void)p;
	(void)cb;
	(void)u;
	ft_putendl(errinfo);
}

struct s_cl	*cl_init(const char *src, size_t size)
{
	struct s_cl	*cl;
	int			err;

	cl = malloc(sizeof(struct s_cl));
	if (clGetPlatformIDs(1, &cl->platform, NULL) != CL_SUCCESS)
		ft_putendl("Failed to get platform");
	else if (clGetDeviceIDs(cl->platform, CL_DEVICE_TYPE_GPU, 1, &cl->device,
		NULL) != CL_SUCCESS)
		ft_putendl("Failed to get device");
	else if ((cl->context = clCreateContext(NULL, 1, &cl->device, opencl_error,
		NULL, &err)) == NULL)
		ft_putendl("Failed to create cl context");
	else if ((cl->queue = clCreateCommandQueue(cl->context, cl->device, 0,
		&err)) == NULL)
		ft_putendl("Failed to create command queue");
	else if ((cl->program = clCreateProgramWithSource(cl->context, 1, &src,
		&size, &err)) == NULL)
		ft_putendl("Failed to create program");
	else if ((clBuildProgram(cl->program, 1, &cl->device, NULL, NULL, NULL))
		!= CL_SUCCESS)
		ft_putendl("Failed to build program");
	else
		return (cl);
	cl_release(cl);
	return (NULL);
}

void		cl_release(struct s_cl *cl)
{
	if (cl->context)
		clReleaseContext(cl->context);
	if (cl->queue)
		clReleaseCommandQueue(cl->queue);
	if (cl->program)
		clReleaseProgram(cl->program);
	free(cl);
}
