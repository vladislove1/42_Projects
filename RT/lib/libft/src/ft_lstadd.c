/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvikhrov <yvikhrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 20:57:37 by yvikhrov          #+#    #+#             */
/*   Updated: 2018/07/15 18:18:03 by yvikhrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lst_push_front(t_list **alst, void *data)
{
	t_list	*head;
	t_list	*new;

	if (!data || !alst)
		return ;
	new = ft_lstnew(data);
	head = *alst;
	if (!head)
		*alst = new;
	else
	{
		*alst = new;
		new->next = head;
	}
}

void	ft_lst_push_back(t_list **alst, t_list *new)
{
	t_list	*head;

	if (!new || !alst)
		return ;
	head = *alst;
	if (!head)
		*alst = new;
	else
	{
		while (head->next)
			head = head->next;
		head->next = new;
	}
}
