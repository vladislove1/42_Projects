/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liza <liza@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/07 21:00:53 by liza              #+#    #+#             */
/*   Updated: 2018/09/07 23:20:50 by liza             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CL_H
# define CL_H

# include <OpenCL/OpenCL.h>
# include <stddef.h>
# include <stdbool.h>

struct s_cl;
struct				s_cl_buffer
{
	cl_mem			cl;
	size_t			size;
};

struct				s_cl_kernel
{
	cl_kernel cl;
};

struct s_cl			*cl_init(const char *source, size_t size);
void				cl_release(struct s_cl *cl);

struct s_cl_buffer	*cl_buffer_init(struct s_cl *cl, size_t size, void *ptr);
bool				cl_buffer_write(struct s_cl *cl, struct s_cl_buffer *buff,
					size_t size, void *src);
bool				cl_buffer_read(struct s_cl *cl, struct s_cl_buffer *buff,
					size_t size, void *dest);
void				cl_buffer_release(struct s_cl_buffer *buff);

struct s_cl_kernel	*cl_kernel_init(struct s_cl *cl, const char *name);
bool				cl_kernel_run(struct s_cl *cl, struct s_cl_kernel *kernel,
					size_t width, size_t height);
void				cl_kernel_release(struct s_cl_kernel *kernel);

#endif
