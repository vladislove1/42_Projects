/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_kernel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liza <liza@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 12:35:49 by liza              #+#    #+#             */
/*   Updated: 2018/09/08 12:38:07 by liza             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_private.h"

struct s_cl_kernel	*cl_kernel_init(struct s_cl *cl, const char *name)
{
	struct s_cl_kernel	*kernel;
	int					err;

	kernel = malloc(sizeof(struct s_cl_kernel));
	if ((kernel->cl = clCreateKernel(cl->program, name, &err)) != NULL)
		return (kernel);
	cl_kernel_release(kernel);
	return (NULL);
}

bool				cl_kernel_run(struct s_cl *cl, struct s_cl_kernel *kernel,
	size_t width, size_t height)
{
	const size_t	global_work_size[] = {width, height};
	const size_t	local_work_size[] = {16, 16};
	int				err;

	err = clEnqueueNDRangeKernel(cl->queue, kernel->cl, 2, NULL,
		global_work_size, local_work_size, 0, NULL, NULL);
	return (err == CL_SUCCESS);
}

void				cl_kernel_release(struct s_cl_kernel *kernel)
{
	clReleaseKernel(kernel->cl);
	free(kernel);
}
