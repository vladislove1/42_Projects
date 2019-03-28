/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvikhrov <yvikhrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 16:18:59 by yvikhrov          #+#    #+#             */
/*   Updated: 2017/10/29 17:22:15 by yvikhrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isspace(int symb)
{
	unsigned char	c;

	c = (unsigned char)symb;
	return (c == '\t' || c == '\n' || c == '\v' || c == ' ' || c == '\f'
			|| c == '\r');
}