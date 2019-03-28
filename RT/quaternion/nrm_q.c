/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nrm_q.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdomozhy <pdomozhy@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 20:59:00 by pdomozhy          #+#    #+#             */
/*   Updated: 2018/01/20 20:59:02 by pdomozhy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quaternion.h"

t_q					nrm_q(t_q a)
{
	t_q				tmp;
	float			mag;

	mag = mag_q(a);
	if (!mag)
		tmp = (t_q){0, 0, 0, 0};
	else
		tmp = scl_q(a, 1 / mag);
	return (tmp);
}
