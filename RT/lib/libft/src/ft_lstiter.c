/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvikhrov <yvikhrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 21:02:11 by yvikhrov          #+#    #+#             */
/*   Updated: 2018/07/15 18:18:40 by yvikhrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(const t_list *lst, void (*f)(void *content, void *ctx),
																	void *ctx)
{
	t_list *head;

	if (!(head = (t_list*)lst) || !f)
		return ;
	while (head)
	{
		f(head->content, ctx);
		head = head->next;
	}
}
