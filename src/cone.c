/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasyush <mmasyush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 15:15:11 by mmasyush          #+#    #+#             */
/*   Updated: 2019/10/29 17:28:46 by mmasyush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv.h"

t_roots		inter_cone(t_vector camera, t_vector d, int n, t_rtv *rtv)
{
	t_inter	fo;
	double	value;
	double	d_dir;
	double	oc_dir;

	fo.oc = camera - rtv->map.obj[n].cone.o;
	d_dir = vect_dot(d, rtv->map.obj[n].cone.dir);
	oc_dir = vect_dot(fo.oc, rtv->map.obj[n].cone.dir);
	value = (1 + rtv->map.obj[n].cone.ang * rtv->map.obj[n].cone.ang);
	fo.k1 = vect_dot(d, d) - value * d_dir * d_dir;
	fo.k2 = vect_dot(d, fo.oc) - value * d_dir * oc_dir;
	fo.k3 = vect_dot(fo.oc, fo.oc) - value * oc_dir * oc_dir;
	fo.dis = fo.k2 * fo.k2 - fo.k1 * fo.k3;
	if (fo.dis < 0)
		return ((t_roots){T_MAX + 1, T_MAX + 1});
	fo.dis = sqrt(fo.dis);
	return ((t_roots){(-fo.k2 + fo.dis) /
		(fo.k1), (-fo.k2 - fo.dis) / (fo.k1)});
}

t_vector	cone_norm(t_rtv *rtv, t_calc *c)
{
	double	m;

	c->point = c->camera + vect_mult(c->dir, c->check.min_dist);
	m = vect_dot(c->dir, rtv->map.obj[c->check.close_obj].cone.dir) * \
		c->check.min_dist + vect_dot(c->camera - \
		rtv->map.obj[c->check.close_obj].cone.o, \
		rtv->map.obj[c->check.close_obj].cone.dir);
	c->normal = c->point - rtv->map.obj[c->check.close_obj].cone.o - \
		vect_mult(rtv->map.obj[c->check.close_obj].cone.dir, m * \
		(1 + rtv->map.obj[c->check.close_obj].cone.ang * \
		rtv->map.obj[c->check.close_obj].cone.ang));
	c->normal = vect_div(c->normal, vect_len(c->normal));
	c->dir = -c->dir;
	return (vect_mult(rtv->map.obj[c->check.close_obj].cone.col, \
		calc_light(rtv, c, rtv->map.obj[c->check.close_obj].cone.spec)));
}

int			save_cone(t_map *map, char *line)
{
	char		*l;

	l = ft_strtrim(line);
	if (ft_strncmp("specular = ", l, ft_strlen("specular = ")) == 0)
		map->obj[map->onum].cone.spec = get_int(l, \
			(int)ft_strlen("specular = "), (int)ft_strlen(l));
	else if (ft_strncmp("angle = ", l, ft_strlen("angle = ")) == 0)
		map->obj[map->onum].cone.ang = get_double(l, \
			(int)ft_strlen("angle = "), (int)ft_strlen(l));
	else if (ft_strncmp("position = ", l, ft_strlen("position = ")) == 0)
		map->obj[map->onum].cone.o = get_vect(l);
	else if (ft_strncmp("direction = ", l, ft_strlen("direction = ")) == 0)
		map->obj[map->onum].cone.dir = get_vect(l);
	else if (ft_strncmp("color = ", l, ft_strlen("color = ")) == 0)
		map->obj[map->onum].cone.col = get_vect(l);
	else
		ft_error(BADLINE);
	free(l);
	return (1);
}
