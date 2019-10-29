/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasyush <mmasyush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 16:56:55 by mmasyush          #+#    #+#             */
/*   Updated: 2019/10/29 15:33:41 by mmasyush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv.h"

int	main(int argc, char **argv)
{
	t_rtv	rtv;

	if (argc == 2)
	{
		if (!read_scene(&rtv.map, argv[1]))
			ft_error(BADFILE);
		if (!init_sdl(&rtv.sdl))
			return (1);
		loop(&rtv);
		system("leaks rtv");
	}
	else
		return (usage());
}
