/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasyush <mmasyush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 15:15:11 by mmasyush          #+#    #+#             */
/*   Updated: 2019/10/23 20:16:59 by mmasyush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv.h"

t_inter     inter_cone(t_vector camera, t_vector d, int n, t_rtv *rtv)
{
    t_vector c = rtv->map.obj[n].cone.o;
    t_vector oc;
    oc = camera - c;
    double d_dir = vect_dot(d, rtv->map.obj[n].cone.dir);
    double oc_dir = vect_dot(oc, rtv->map.obj[n].cone.dir);
	double value = (1 + rtv->map.obj[n].cone.ang * rtv->map.obj[n].cone.ang);
    double k1 = vect_dot(d, d) - value * d_dir * d_dir;
    double k2 = vect_dot(d, oc) - value * d_dir * oc_dir;
    double k3 = vect_dot(oc, oc) - value * oc_dir * oc_dir;

    double dis = k2 * k2 - k1 * k3;
    if (dis < 0)
        return ((t_inter){T_MAX, T_MAX});
    return ((t_inter){(-k2 + sqrt(dis)) / (k1), (-k2 - sqrt(dis)) / (k1)});
}

t_vector	    cone_norm(t_rtv *rtv, t_calc *c)
{
	double	m;

	t_vector p = c->camera + vect_mult(c->dir, c->check.min_dist);
	m = vect_dot(c->dir, rtv->map.obj[c->check.close_obj].cone.dir) * \
	c->check.min_dist + vect_dot(c->camera - rtv->map.obj[c->check.close_obj].cone.o, rtv->map.obj[c->check.close_obj].cone.dir);
	t_vector normal = p - rtv->map.obj[c->check.close_obj].cone.o - vect_mult(rtv->map.obj[c->check.close_obj].cone.dir, m * (1 + rtv->map.obj[c->check.close_obj].cone.ang * rtv->map.obj[c->check.close_obj].cone.ang));
	normal = vect_div(normal, vect_len(normal));
	return (vect_mult(rtv->map.obj[c->check.close_obj].cone.col,  calc_light(rtv, p, normal, rtv->map.obj[c->check.close_obj].cone.spec, -c->dir)));
}

int			save_cone(t_map *map, char *line)
{
	char		*l;

	l = ft_strtrim(line);
	if (ft_strncmp("specular = ", l, ft_strlen("specular = ")) == 0)
		map->obj[map->onum].cone.spec = get_int(l, \
			(int)ft_strlen("specular = "), (int)ft_strlen(l));
	if (ft_strncmp("radius = ", l, ft_strlen("radius = ")) == 0)
		map->obj[map->onum].cone.rad = get_double(l, \
			(int)ft_strlen("radius = "), (int)ft_strlen(l));
	if (ft_strncmp("angle = ", l, ft_strlen("angle = ")) == 0)
		map->obj[map->onum].cone.ang = get_double(l, \
			(int)ft_strlen("angle = "), (int)ft_strlen(l));
	if (ft_strncmp("center = ", l, ft_strlen("center = ")) == 0)
		map->obj[map->onum].cone.o = get_vect(l);
	if (ft_strncmp("direction = ", l, ft_strlen("direction = ")) == 0)
		map->obj[map->onum].cone.dir = get_vect(l);
	map->obj[map->onum].cone.dir = vect_div(map->obj[map->onum].cone.dir, vect_len(map->obj[map->onum].cone.dir));
	if (ft_strncmp("color = ", l, ft_strlen("color = ")) == 0)
		map->obj[map->onum].cone.col = get_vect(l);
	return (1);
}