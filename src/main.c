/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasyush <mmasyush@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 16:56:55 by mmasyush          #+#    #+#             */
/*   Updated: 2019/09/17 16:56:55 by mmasyush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv.h"

int    main(int argc, char **argv)
{
    t_rtv   rtv;

    if (argc == 2)
    {
        if(!read_scene(&rtv.map, argv[1]))
            return (1);
       
        if(!init_sdl(&rtv.sdl))
            return (1);
      
        // printf("%f\n", rtv.map.obj[0].sphere.col[1]);
        // printf("%f\n", rtv.map.obj[0].sphere.col[2]);

        // printf("%f\n", rtv.map.obj[1].sphere.col[0]);
		// printf("%f\n", rtv.map.obj[1].sphere.col[1]);
        // printf("%f\n", rtv.map.obj[1].sphere.col[2]);

        // printf("%f\n", rtv.map.obj[2].sphere.col[0]);
        // printf("%f\n", rtv.map.obj[2].sphere.col[1]);
        // printf("%f\n", rtv.map.obj[2].sphere.col[2]);
        loop(&rtv);
    }
    else
        return (usage());
}