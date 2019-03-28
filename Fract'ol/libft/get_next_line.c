/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmikhajl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 17:42:15 by vmikhajl          #+#    #+#             */
/*   Updated: 2017/12/04 17:42:16 by vmikhajl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_gnl		*create_l(t_list_l **lst, int fd)
{
	t_list_l		*temp;

	temp = *lst;
	while (temp)
	{
		if (temp->gnl->fd == fd)
		{
			return ((temp->gnl));
		}
		temp = temp->next;
	}
	temp = (t_list_l *)malloc(sizeof(t_list_l));
	temp->gnl = (t_gnl *)(malloc(sizeof(t_gnl)));
	temp->gnl->fd = fd;
	temp->gnl->buf = ft_strnew(BUFF_SIZE);
	temp->gnl->str = ft_strnew(0);
	temp->next = *lst;
	*lst = temp;
	return ((temp->gnl));
}

static void			free_list(t_list_l **lst, int fd)
{
	t_gnl			*gnl;
	t_list_l		**temp;
	t_list_l		*ptr;

	temp = lst;
	while (*temp)
	{
		gnl = ((*temp)->gnl);
		if (gnl->fd == fd)
			break ;
		*temp = ((*temp)->next);
	}
	if (*temp)
	{
		ptr = (*temp)->next;
		ft_strdel(&(gnl->buf));
		if (gnl->str)
		{
			ft_strdel(&(gnl->str));
		}
		ft_memdel((void **)&gnl);
		ft_memdel((void **)temp);
		*temp = ptr;
	}
}

static int			find_endl(char *str)
{
	int				i;

	i = 0;
	while (str[i] != '\n' && str[i])
		i++;
	if (str[i] == '\n')
	{
		str[i] = '\0';
		return (i);
	}
	else
		return (-1);
}

static int			check(t_gnl *gnl, char **line)
{
	char			*ptr;
	int				next_l;

	if (gnl->str)
	{
		ptr = gnl->str;
		gnl->str = ft_strjoin(gnl->str, gnl->buf);
		ft_bzero(gnl->buf, BUFF_SIZE + 1);
		free(ptr);
		next_l = find_endl(gnl->str);
		if (next_l > -1)
		{
			*line = ft_strdup(gnl->str);
			ptr = gnl->str;
			gnl->str = ft_strdup(gnl->str + next_l + 1);
			free(ptr);
			return (1);
		}
	}
	return (0);
}

int					get_next_line(int const fd, char **line)
{
	t_gnl			*gnl;
	int				ret;
	static t_list_l	*lst;
	char			*temp;

	temp = ft_strnew(BUFF_SIZE);
	if (!line || fd < 0 || BUFF_SIZE <= 0 || (ret = read(fd, temp, 0)) < 0)
	{
		free(temp);
		return (-1);
	}
	free(temp);
	gnl = create_l(&lst, fd);
	while ((gnl->size = read(gnl->fd, gnl->buf, BUFF_SIZE)) > 0)
		if ((ret = check(gnl, line)) != 0)
			return (ret);
	if ((ret = check(gnl, line)) > 0)
		return (1);
	else if (ft_strlen(gnl->str) > 0)
	{
		*line = ft_strdup(gnl->str);
		free_list(&lst, fd);
		return (1);
	}
	return (ret);
}
