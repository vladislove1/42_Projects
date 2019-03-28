/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_reading.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liza <liza@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 13:43:36 by liza              #+#    #+#             */
/*   Updated: 2019/02/02 23:39:01 by liza             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

size_t					read_file_fd(int fd, char **file)
{
	int					size;
	ssize_t				begin;
	int					ret;

	size = lseek(fd, 0, SEEK_END);
	if (size == 0)
		return (0);
	*file = malloc(size + 1);
	(*file)[size] = '\0';
	begin = lseek(fd, 0, SEEK_SET);
	ret = read(fd, *file, size);
	if (ret != size)
	{
		perror("read file");
		free(file);
		return (0);
	}
	return (size);
}

size_t					read_file(char *path, char **file)
{
	int					fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		perror("Read file");
		return (0);
	}
	return (read_file_fd(fd, file));
}
