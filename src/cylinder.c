/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasyush <mmasyush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 15:14:05 by mmasyush          #+#    #+#             */
/*   Updated: 2019/10/28 19:19:35 by mmasyush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv.h"

t_roots		inter_cyl(t_vector camera, t_vector d, int n, t_rtv *rtv)
{
	t_inter	fo;
	double	d_dir;
	double	oc_dir;
	double	r;

	r = rtv->map.obj[n].cylinder.rad;
	fo.oc = camera - rtv->map.obj[n].cylinder.o;
	d_dir = vect_dot(d, rtv->map.obj[n].cylinder.dir);
	oc_dir = vect_dot(fo.oc, rtv->map.obj[n].cylinder.dir);
	fo.k1 = vect_dot(d, d) - d_dir * d_dir;
	fo.k2 = vect_dot(d, fo.oc) - d_dir * oc_dir;
	fo.k3 = vect_dot(fo.oc, fo.oc) - oc_dir * oc_dir - r * r;
	fo.dis = fo.k2 * fo.k2 - fo.k1 * fo.k3;
	if (fo.dis < 0)
		return ((t_roots){T_MAX, T_MAX});
	return ((t_roots){(-fo.k2 + sqrt(fo.dis)) /
		(fo.k1), (-fo.k2 - sqrt(fo.dis)) / (fo.k1)});
}

t_vector	cyl_norm(t_rtv *rtv, t_calc *c)
{
	double	m;

	c->point = c->camera + vect_mult(c->dir, c->check.min_dist);
	m = vect_dot(c->dir, rtv->map.obj[c->check.close_obj].cylinder.dir) * \
		c->check.min_dist + vect_dot(c->camera - \
		rtv->map.obj[c->check.close_obj].cylinder.o, \
		rtv->map.obj[c->check.close_obj].cylinder.dir);
	c->normal = c->point - rtv->map.obj[c->check.close_obj].cylinder.o - \
		vect_mult(rtv->map.obj[c->check.close_obj].cylinder.dir, m);
	c->normal = vect_div(c->normal, vect_len(c->normal));
	c->dir = -c->dir;
	return (vect_mult(rtv->map.obj[c->check.close_obj].cylinder.col,
		calc_light(rtv, c, rtv->map.obj[c->check.close_obj].cylinder.spec)));
}

int			save_cyl(t_map *map, char *line)
{
	char		*l;

	l = ft_strtrim(line);
	if (ft_strncmp("specular = ", l, ft_strlen("specular = ")) == 0)
		map->obj[map->onum].cylinder.spec = get_int(l, \
		(int)ft_strlen("specular = "), (int)ft_strlen(l));
	if (ft_strncmp("radius = ", l, ft_strlen("radius = ")) == 0)
		map->obj[map->onum].cylinder.rad = get_double(l, \
		(int)ft_strlen("radius = "), (int)ft_strlen(l));
	if (ft_strncmp("position = ", l, ft_strlen("position = ")) == 0)
		map->obj[map->onum].cylinder.o = get_vect(l);
	if (ft_strncmp("direction = ", l, ft_strlen("direction = ")) == 0)
		map->obj[map->onum].cylinder.dir = get_vect(l);
	if (ft_strncmp("color = ", l, ft_strlen("color = ")) == 0)
		map->obj[map->onum].cylinder.col = get_vect(l);
	return (1);
}
