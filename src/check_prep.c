/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_prep.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasyush <mmasyush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 20:06:15 by mmasyush          #+#    #+#             */
/*   Updated: 2019/10/30 18:15:21 by mmasyush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv.h"

void	check_sphere(t_sphere *obj)
{
	if (obj->spec > 1000 || obj->spec < -1 || obj->rad < 0)
		ft_error(BADSPH);
	check_color(obj->col);
}

void	check_cone(t_cone *obj)
{
	if (obj->spec > 1000 || obj->spec < -1 || obj->ang < 0)
		ft_error(BADCONE);
	check_color(obj->col);
	obj->dir = vect_div(obj->dir, vect_len(obj->dir));
	obj->ang = tan(obj->ang / 2 * M_PI / 180);
}

void	check_cyl(t_cylinder *obj)
{
	if (obj->spec > 1000 || obj->spec < -1 || obj->rad < 0)
		ft_error(BADCYL);
	check_color(obj->col);
	obj->dir = vect_div(obj->dir, vect_len(obj->dir));
}

void	check_plane(t_plane *obj)
{
	if (obj->spec > 1000 || obj->spec < -1)
		ft_error(BADPLN);
	check_color(obj->col);
	obj->norm = vect_div(obj->norm, vect_len(obj->norm));
}

void	prepare_all(t_map *map)
{
	int i;

	i = -1;
	while (++i < map->onum)
	{
		if (map->olist[i] == SPHERE)
			check_sphere(&map->obj[i].sphere);
		if (map->olist[i] == CONE)
			check_cone(&map->obj[i].cone);
		if (map->olist[i] == CYLINDER)
			check_cyl(&map->obj[i].cylinder);
		if (map->olist[i] == PLANE)
			check_plane(&map->obj[i].plane);
	}
	i = -1;
	while (++i < map->lnum)
		if (map->light[i].i < 0 || map->light[i].i > 1)
			ft_error(BADLIG);
	if (map->onum <= 0 || map->lnum <= 0)
		ft_error(BADFILE);
	dir_angls(&map->camera);
}
