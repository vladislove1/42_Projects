/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_private.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liza <liza@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/07 22:19:36 by liza              #+#    #+#             */
/*   Updated: 2018/09/08 12:38:16 by liza             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CL_PRIVATE_H
# define CL_PRIVATE_H

# include "cl.h"

struct					s_cl
{
	cl_platform_id		platform;
	cl_device_id		device;
	cl_context			context;
	cl_command_queue	queue;
	cl_program			program;
};

#endif
