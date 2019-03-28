/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmikhajl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 17:42:22 by vmikhajl          #+#    #+#             */
/*   Updated: 2017/12/04 17:42:24 by vmikhajl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stdlib.h>
# include "libft.h"
# define BUFF_SIZE 9999

typedef struct		s_gnl
{
	char		*buf;
	char		*str;
	int			size;
	int			fd;
}					t_gnl;

typedef struct		s_list_l
{
	struct s_gnl			*gnl;
	struct s_list_l			*next;
}					t_list_l;

int					get_next_line(int const fd, char **line);

#endif
