/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liza <liza@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 14:11:35 by yvikhrov          #+#    #+#             */
/*   Updated: 2018/09/14 21:51:20 by liza             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_app	*get_app(void)
{
	static t_app *app = NULL;

	if (app == NULL)
	{
		app = (t_app*)malloc(sizeof(t_app));
		ft_memset(app, 0, sizeof(t_app));
	}
	return (app);
}

static void		print_usage(void)
{
	ft_putendl("Usage: ./rtv1 'scenes/scene'");
	exit(EXIT_FAILURE);
}

int				main(int ac, char **av)
{
	t_app	*app;

	app = get_app();
	if (ac != 2)
	{
		print_usage();
		return (0);
	}
	if (init(app, av[1]))
		main_loop(app);
	return (0);
}
