/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdomozhy <pdomozhy@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 20:33:15 by pdomozhy          #+#    #+#             */
/*   Updated: 2018/01/20 20:33:18 by pdomozhy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUATERNION_H
# define QUATERNION_H

# include <math.h>

typedef	struct		s_q
{
	float			x;
	float			y;
	float			z;
	float			w;
}					t_q;

t_q					add_q(t_q a, t_q b);
t_q					chb_q(t_q a, t_q b, t_q c);
float				cos_q(t_q a, t_q b);
t_q					crs_q(t_q a, t_q b);
int					cmp_q(t_q a, t_q b);
float				dot_q(t_q a, t_q b);
float				dst_q(t_q a, t_q b);
t_q					lnr_q(t_q a, t_q b, float c);
float				mag_q(t_q a);
t_q					nrm_q(t_q a);
t_q					opp_q(t_q a);
t_q					rot_q(t_q a, t_q b, float c);
t_q					scl_q(t_q a, float k);
float				sqr_q(t_q a);
t_q					sub_q(t_q a, t_q b);

#endif
