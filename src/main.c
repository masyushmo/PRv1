/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasyush <mmasyush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 16:56:55 by mmasyush          #+#    #+#             */
/*   Updated: 2019/10/30 18:55:24 by mmasyush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv.h"

int	loop(t_rtv *rtv)
{
	rtv->quit = 0;
	while (rtv->quit == 0)
	{
		keyses(rtv);
		split(rtv);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_rtv	rtv;

	if (argc == 2)
	{
		printf("%s\n", argv[1]);
		if ((ft_strncmp("scenes/", argv[1], ft_strlen("scenes/"))) || \
			!read_scene(&rtv.map, argv[1]))
			ft_error(BADFILE);
		if (!init_sdl(&rtv.sdl))
			return (1);
		loop(&rtv);
	}
	else
		return (usage());
}
