/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_buffer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liza <liza@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 13:14:29 by liza              #+#    #+#             */
/*   Updated: 2018/09/08 13:17:49 by liza             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_private.h"

struct s_cl_buffer	*cl_buffer_init(struct s_cl *cl, size_t size, void *ptr)
{
	struct s_cl_buffer	*buffer;
	int					err;
	int					flags;

	flags = CL_MEM_READ_WRITE;
	buffer = malloc(sizeof(struct s_cl_buffer));
	if (ptr)
		flags |= CL_MEM_COPY_HOST_PTR;
	if ((buffer->cl = clCreateBuffer(cl->context, flags, size, ptr, &err))
		!= NULL)
		return (buffer);
	cl_buffer_release(buffer);
	return (false);
}

bool				cl_buffer_write(struct s_cl *cl, struct s_cl_buffer *buff,
	size_t size, void *src)
{
	int err;

	err = clEnqueueWriteBuffer(cl->queue, buff->cl, CL_TRUE, 0, size, src,
		0, NULL, NULL);
	return (err == CL_SUCCESS);
}

bool				cl_buffer_read(struct s_cl *cl, struct s_cl_buffer *buff,
	size_t size, void *dest)
{
	int err;

	err = clEnqueueReadBuffer(cl->queue, buff->cl, CL_TRUE, 0, size, dest,
		0, NULL, NULL);
	return (err == CL_SUCCESS);
}

void				cl_buffer_release(struct s_cl_buffer *buffer)
{
	if (buffer->cl)
		clReleaseMemObject(buffer->cl);
	free(buffer);
}
