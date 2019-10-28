/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasyush <mmasyush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 15:12:05 by mmasyush          #+#    #+#             */
/*   Updated: 2019/10/28 19:49:05 by mmasyush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv.h"

t_roots		inter_sphere(t_vector camera, t_vector d, int n, t_rtv *rtv)
{
	t_inter	fo;
	double	r;

	fo.oc = camera - rtv->map.obj[n].sphere.o;
	r = rtv->map.obj[n].sphere.rad;
	fo.k1 = vect_dot(d, d);
	fo.k2 = vect_dot(d, fo.oc);
	fo.k3 = vect_dot(fo.oc, fo.oc) - r * r;
	fo.dis = fo.k2 * fo.k2 - fo.k1 * fo.k3;
	if (fo.dis < 0)
		return ((t_roots){T_MAX, T_MAX});
	return ((t_roots){(-fo.k2 + sqrt(fo.dis)) / (fo.k1), \
		(-fo.k2 - sqrt(fo.dis)) / (fo.k1)});
}

t_vector	sphere_norm(t_rtv *rtv, t_calc *c)
{
	c->point = c->camera + vect_mult(c->dir, c->check.min_dist);
	c->normal = c->point - rtv->map.obj[c->check.close_obj].sphere.o;
	c->normal = vect_div(c->normal, vect_len(c->normal));
	c->dir = -c->dir;
	return (vect_mult(rtv->map.obj[c->check.close_obj].sphere.col, \
		calc_light(rtv, c, rtv->map.obj[c->check.close_obj].sphere.spec)));
}

int			save_sphere(t_map *map, char *line)
{
	char		*l;

	l = ft_strtrim(line);
	if (ft_strncmp("specular = ", l, ft_strlen("specular = ")) == 0)
		map->obj[map->onum].sphere.spec = get_int(l, \
			(int)ft_strlen("specular = "), (int)ft_strlen(l));
	if (ft_strncmp("radius = ", l, ft_strlen("radius = ")) == 0)
		map->obj[map->onum].sphere.rad = get_double(l, \
			(int)ft_strlen("radius = "), (int)ft_strlen(l));
	if (ft_strncmp("position = ", l, ft_strlen("position = ")) == 0)
		map->obj[map->onum].sphere.o = get_vect(l);
	if (ft_strncmp("color = ", l, ft_strlen("color = ")) == 0)
		map->obj[map->onum].sphere.col = get_vect(l);
	return (1);
}
