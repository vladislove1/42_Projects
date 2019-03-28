/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rot_q.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdomozhy <pdomozhy@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 20:59:00 by pdomozhy          #+#    #+#             */
/*   Updated: 2018/01/20 20:59:02 by pdomozhy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quaternion.h"

t_q					rot_q(t_q a, t_q b, float c)
{
	t_q				tmp;
	float			cos_a;
	float			sin_a;

	cos_a = cos(c);
	sin_a = sin(c);
	tmp = add_q(scl_q(a, cos_a), scl_q(crs_q(b, a), sin_a));
	tmp = add_q(tmp, scl_q(b, (1 - cos_a) * dot_q(a, b)));
	return (tmp);
}
