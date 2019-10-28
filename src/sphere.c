/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasyush <mmasyush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 15:12:05 by mmasyush          #+#    #+#             */
/*   Updated: 2019/10/28 18:25:01 by mmasyush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv.h"

t_inter     inter_sphere(t_vector camera, t_vector d, int n, t_rtv *rtv)
{
	t_vector c = rtv->map.obj[n].sphere.o;
	double r = rtv->map.obj[n].sphere.rad;
	t_vector oc;
	oc = camera - c;
	
	double k1 = vect_dot(d, d);
	double k2 = vect_dot(d, oc);
	double k3 = vect_dot(oc, oc) - r * r;

	double dis = k2 * k2 - k1 * k3;
	if (dis < 0)
		return ((t_inter){T_MAX, T_MAX});
	return ((t_inter){(-k2 + sqrt(dis)) / (k1), (-k2 - sqrt(dis)) / (k1)});
}

t_vector	    sphere_norm(t_rtv *rtv, t_calc *c)
{
	t_vector p = c->camera + vect_mult(c->dir, c->check.min_dist);
	t_vector normal = p - rtv->map.obj[c->check.close_obj].sphere.o;
	normal = vect_div(normal, vect_len(normal));
	return (vect_mult(rtv->map.obj[c->check.close_obj].sphere.col, calc_light(rtv, p, normal, rtv->map.obj[c->check.close_obj].sphere.spec, -c->dir)));
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
