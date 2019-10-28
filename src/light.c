/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasyush <mmasyush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 15:17:06 by mmasyush          #+#    #+#             */
/*   Updated: 2019/10/28 18:25:01 by mmasyush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv.h"

double      calc_light(t_rtv *rtv, t_vector P, t_vector normal, int spec, t_vector d)
{
	int i = -1;
	double inte = 0.0;
	double hz;
	double zz;
	t_raycheck shadow;
	t_vector light_d;

	while (++i < rtv->map.lnum)
	{
		if (rtv->map.light[i].type == AMBIENT) 
		{
			inte += rtv->map.light[i].i;
		}
		else
		{
			if (rtv->map.light[i].type == POINT)
				light_d = rtv->map.light[i].vect - P;
			else
				light_d = rtv->map.light[i].vect;
		
			shadow = close_inter(P, light_d, 0.001, rtv);
			if (shadow.close_obj != -1)
				continue;
			
			hz = vect_dot(normal, light_d);
			if (hz > 0)
				inte += (rtv->map.light[i].i * hz / \
						(vect_len(light_d) * vect_len(normal)));
			if (spec != -1)
			{
				t_vector light_r  = vect_mult(vect_mult(normal, 2), (vect_dot(normal, light_d))) - light_d;
				zz = vect_dot(light_r, d);
				if (zz > 0)
					inte += (rtv->map.light[i].i * ft_expon((zz / (vect_len(light_r) * vect_len(d))), spec));
			}

		}
	}
	return (inte);
}

int			save_light(t_map *map, char *line)
{
	char		*l;

	l = ft_strtrim(line);
	if (ft_strcmp("type = ambient", l) == 0)
		map->light[map->lnum].type = AMBIENT;
	else if(ft_strcmp("type = direct", l) == 0)
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
