/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_prep.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasyush <mmasyush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 20:06:15 by mmasyush          #+#    #+#             */
/*   Updated: 2019/10/24 14:26:22 by mmasyush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv.h"

void prepare_all(t_map *map)
{
    int i;

    i = -1;
    while (++i < map->onum - map->lnum)
    {
        if (map->olist[i] == SPHERE)
        {
            if (map->obj[i].sphere.spec > 1000 || \
                map->obj[i].sphere.spec < -1 || map->obj[i].sphere.rad < 0)
			    ft_error(BADSPH);
	        check_color(map->obj[i].sphere.col);
        }
        if (map->olist[i] == CONE)
        {
            if (map->obj[i].cone.spec > 1000 || map->obj[i].cone.spec < -1 || \
                map->obj[i].cone.rad < 0 || map->obj[i].cone.ang < 0)
			    ft_error(BADCONE);
	        check_color(map->obj[i].cone.col);
            map->obj[i].cone.dir = vect_div(map->obj[i].cone.dir, \
                vect_len(map->obj[i].cone.dir));
            map->obj[i].cone.ang = tan(map->obj[i].cone.ang / 2 * M_PI / 180);
        }
        if (map->olist[i] == CYLINDER)
        {
            if (map->obj[i].cylinder.spec > 1000 ||
                map->obj[i].cylinder.spec < -1 ||
                map->obj[i].cylinder.rad < 0)
			    ft_error(BADCYL);
	        check_color(map->obj[i].cylinder.col);
            map->obj[i].cylinder.dir = vect_div(map->obj[i].cylinder.dir, \
                vect_len(map->obj[i].cylinder.dir));
        }
        if (map->olist[i] == PLANE)
        {
            if (map->obj[i].plane.spec > 1000 || map->obj[i].plane.spec < -1)
			    ft_error(BADPLN);
	        check_color(map->obj[i].plane.col);
            map->obj[i].plane.norm = vect_div(map->obj[i].plane.norm, \
                vect_len(map->obj[i].plane.norm));
        }
    }
}
