/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasyush <mmasyush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 15:14:34 by mmasyush          #+#    #+#             */
/*   Updated: 2019/10/28 18:24:15 by mmasyush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv.h"

t_inter     inter_plane(t_vector camera, t_vector d, int n, t_rtv *rtv)
{ 
	double d_dir = vect_dot(d, rtv->map.obj[n].plane.norm);
	if (d_dir < 0)
	return ((t_inter){T_MAX + 1, T_MAX + 1});
	else
	{
		double c_norm = vect_dot(camera - rtv->map.obj[n].plane.o, rtv->map.obj[n].plane.norm);
		return ((t_inter){T_MAX + 1, -c_norm / d_dir});
	}
}

t_vector	    plane_norm(t_rtv *rtv, t_calc *calc)
{
	t_vector normal;

	t_vector p = calc->camera + vect_mult(calc->dir, calc->check.min_dist);
	if (vect_dot(calc->dir, rtv->map.obj[calc->check.close_obj].plane.norm) < 0)
		normal = rtv->map.obj[calc->check.close_obj].plane.norm;
	else
		normal = -rtv->map.obj[calc->check.close_obj].plane.norm;
	return (vect_mult(rtv->map.obj[calc->check.close_obj].plane.col,  calc_light(rtv, p, normal, rtv->map.obj[calc->check.close_obj].plane.spec, -calc->dir)));
}

int			save_plane(t_map *map, char *line)
{
	char		*l;

	l = ft_strtrim(line);
	if (ft_strncmp("specular = ", l, ft_strlen("specular = ")) == 0)
		map->obj[map->onum].plane.spec = get_int(l, \
			(int)ft_strlen("specular = "), (int)ft_strlen(l));
	if (ft_strncmp("normal = ", l, ft_strlen("normal = ")) == 0)
		map->obj[map->onum].plane.norm = get_vect(l);
	if (ft_strncmp("position = ", l, ft_strlen("position = ")) == 0)
		map->obj[map->onum].plane.o = get_vect(l);
	if (ft_strncmp("color = ", l, ft_strlen("color = ")) == 0)
		map->obj[map->onum].plane.col = get_vect(l);
	return (1);
}
