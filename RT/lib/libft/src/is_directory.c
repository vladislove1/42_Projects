/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_directory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvikhrov <yvikhrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 18:56:42 by yvikhrov          #+#    #+#             */
/*   Updated: 2018/06/10 18:57:40 by yvikhrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	is_directory(char *path)
{
	int fd;

	if ((fd = open(path, O_RDONLY | O_DIRECTORY)) == -1)
		return (false);
	close(fd);
	return (true);
}
