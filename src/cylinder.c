/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasyush <mmasyush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 15:14:05 by mmasyush          #+#    #+#             */
/*   Updated: 2019/10/23 20:46:49 by mmasyush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv.h"

t_inter     inter_cyl(t_vector camera, t_vector d, int n, t_rtv *rtv)
{
	printf("dgsgdsgsd");
    t_vector c = rtv->map.obj[n].cylinder.o;
    double r = rtv->map.obj[n].cylinder.rad;
    t_vector oc;
    oc = camera - c;
    double d_dir = vect_dot(d, rtv->map.obj[n].cylinder.dir);
    double oc_dir = vect_dot(oc, rtv->map.obj[n].cylinder.dir);
    double k1 = vect_dot(d, d) - d_dir * d_dir;
    double k2 = vect_dot(d, oc) - d_dir * oc_dir;
    double k3 = vect_dot(oc, oc) - oc_dir * oc_dir - r * r;

    double dis = k2 * k2 - k1 * k3;
    if (dis < 0)
        return ((t_inter){T_MAX, T_MAX});
    return ((t_inter){(-k2 + sqrt(dis)) / (k1), (-k2 - sqrt(dis)) / (k1)});
}

t_vector	    cyl_norm(t_rtv *rtv, t_calc *calc)
{
	double	m;

	t_vector p = calc->camera + vect_mult(calc->dir, calc->check.min_dist);
	m = vect_dot(calc->dir, rtv->map.obj[calc->check.close_obj].cylinder.dir) * \
	calc->check.min_dist + vect_dot(calc->camera - rtv->map.obj[calc->check.close_obj].cylinder.o, rtv->map.obj[calc->check.close_obj].cylinder.dir);
	t_vector normal = p - rtv->map.obj[calc->check.close_obj].cylinder.o - vect_mult(rtv->map.obj[calc->check.close_obj].cylinder.dir, m);
	normal = vect_div(normal, vect_len(normal));
	return (vect_mult(rtv->map.obj[calc->check.close_obj].cylinder.col,  calc_light(rtv, p, normal, rtv->map.obj[calc->check.close_obj].cylinder.spec, -calc->dir)));
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
	if (ft_strncmp("center = ", l, ft_strlen("center = ")) == 0)
		map->obj[map->onum].cylinder.o = get_vect(l);
	if (ft_strncmp("direction = ", l, ft_strlen("direction = ")) == 0)
		map->obj[map->onum].cylinder.dir = get_vect(l);
	if (ft_strncmp("color = ", l, ft_strlen("color = ")) == 0)
		map->obj[map->onum].cylinder.col = get_vect(l);
	return (1);
}
