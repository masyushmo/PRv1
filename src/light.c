/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasyush <mmasyush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 15:17:06 by mmasyush          #+#    #+#             */
/*   Updated: 2019/10/28 19:37:51 by mmasyush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv.h"

double	add_inte(t_calc *calc, double o_inte, int spec)
{
	double	n_ld;
	double	lr_dir;
	double	inte;

	inte = 0.0;
	n_ld = vect_dot(calc->normal, calc->ld);
	if (n_ld > 0)
		inte += (o_inte * n_ld /
			(vect_len(calc->ld) * vect_len(calc->normal)));
	if (spec != -1)
	{
		calc->lr = vect_mult(vect_mult(calc->normal, 2), \
			(vect_dot(calc->normal, calc->ld))) - calc->ld;
		lr_dir = vect_dot(calc->lr, calc->dir);
		if (lr_dir > 0)
			inte += (o_inte * ft_expon((lr_dir / (vect_len(calc->lr) * \
				vect_len(calc->dir))), spec));
	}
	return (inte);
}

double	calc_light(t_rtv *rtv, t_calc *calc, int spec)
{
	int		i;
	double	inte;

	i = -1;
	inte = 0.0;
	while (++i < rtv->map.lnum)
	{
		if (rtv->map.light[i].type == AMBIENT)
			inte += rtv->map.light[i].i;
		else
		{
			if (rtv->map.light[i].type == POINT)
				calc->ld = rtv->map.light[i].vect - calc->point;
			else
				calc->ld = rtv->map.light[i].vect;
			calc->shadow = close_inter(calc->point, calc->ld, 0.001, rtv);
			if (calc->shadow.close_obj != -1)
				continue;
			inte += add_inte(calc, rtv->map.light[i].i, spec);
		}
	}
	return (inte);
}

int		save_light(t_map *map, char *line)
{
	char		*l;

	l = ft_strtrim(line);
	if (ft_strcmp("type = ambient", l) == 0)
		map->light[map->lnum].type = AMBIENT;
	else if (ft_strcmp("type = direct", l) == 0)
		map->light[map->lnum].type = DIRECT;
	else if (ft_strcmp("type = point", l) == 0)
		map->light[map->lnum].type = POINT;
	if (ft_strncmp("intensity = ", l, ft_strlen("intensity = ")) == 0)
		map->light[map->lnum].i = get_double(l, \
		(int)ft_strlen("intensity = "), (int)ft_strlen(l));
	if ((ft_strncmp("direction = ", l, ft_strlen("direction = ")) == 0) ||
		(ft_strncmp("position = ", l, ft_strlen("position = ")) == 0))
		map->light[map->lnum].vect = get_vect(l);
	return (1);
}
