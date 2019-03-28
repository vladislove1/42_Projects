/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cos_q.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdomozhy <pdomozhy@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 20:59:00 by pdomozhy          #+#    #+#             */
/*   Updated: 2018/01/20 20:59:02 by pdomozhy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quaternion.h"

float				cos_q(t_q a, t_q b)
{
	float			cos;
	float			mag_a;
	float			mag_b;

	mag_a = mag_q(a);
	mag_b = mag_q(b);
	if (!mag_a || !mag_b)
		return (1);
	cos = dot_q(a, b) / mag_a / mag_b;
	return (cos);
}
