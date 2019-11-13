/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasyush <mmasyush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 18:27:37 by mmasyush          #+#    #+#             */
/*   Updated: 2019/11/13 17:07:03 by mmasyush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv.h"
#include <pthread.h>

t_roots		get_roots(t_vector start, t_vector dir, int n, t_rtv *rtv)
{
	t_roots temp;

	temp = (t_roots){0, 0};
	if (rtv->map.olist[n] == SPHERE)
		temp = inter_sphere(start, dir, n, rtv);
	else if (rtv->map.olist[n] == CONE)
		temp = inter_cone(start, dir, n, rtv);
	else if (rtv->map.olist[n] == CYLINDER)
		temp = inter_cyl(start, dir, n, rtv);
	else if (rtv->map.olist[n] == PLANE)
		temp = inter_plane(start, dir, n, rtv);
	return (temp);
}

t_raycheck	close_inter(t_vector start, t_vector dir, t_range *r, t_rtv *rtv)
{
	t_roots		roots;
	t_raycheck	temp;
	int			n;

	temp.min_dist = r->max;
	temp.close_obj = -1;
	n = -1;
	while (++n < rtv->map.onum)
	{
		roots = get_roots(start, dir, n, rtv);
		if (roots[0] > r->min && roots[0] < temp.min_dist)
		{
			temp.min_dist = roots[0];
			temp.close_obj = n;
		}
		if (roots[1] > r->min && roots[1] < temp.min_dist)
		{
			temp.min_dist = roots[1];
			temp.close_obj = n;
		}
	}
	return (temp);
}

t_vector	trace_ray(t_rtv *rtv, t_calc *calc)
{
	t_range range;

	range.max = T_MAX;
	range.min = T_MIN;
	calc->check = close_inter(rtv->map.camera.pos, calc->dir, &range, rtv);
	if (rtv->map.olist[calc->check.close_obj] == SPHERE)
		return (sphere_norm(rtv, calc));
	else if (rtv->map.olist[calc->check.close_obj] == CONE)
		return (cone_norm(rtv, calc));
	else if (rtv->map.olist[calc->check.close_obj] == CYLINDER)
		return (cyl_norm(rtv, calc));
	else if (rtv->map.olist[calc->check.close_obj] == PLANE)
		return (plane_norm(rtv, calc));
	else
		return (BACKROUND);
}

void		*trace_thread(void *data)
{
	int			x;
	int			y;
	t_tdata		*too;
	t_calc		calc;
	t_vector	color;

	too = (t_tdata*)data;
	calc.camera = too->rtv.map.camera.pos;
	y = WIN_H / THREADS * too->num;
	while (y < (WIN_H / THREADS * (too->num + 1)))
	{
		x = -1;
		while (++x < WIN_W)
		{
			calc.dir = rotate_cam(&too->rtv.map.camera,
				canvas_to_view(x - WIN_W / 2, y - WIN_H / 2));
			color = trace_ray(&too->rtv, &calc);
			set_pixel(x, y, rgb_color(color), too->rtv.sdl.surface);
		}
		y++;
	}
	return (NULL);
}

void		split(t_rtv *rtv)
{
	pthread_t	thread[THREADS];
	t_tdata		data[THREADS];
	int			i;

	i = -1;
	while (++i < THREADS)
	{
		data[i].num = i;
		data[i].rtv = *rtv;
		pthread_create(thread + i, NULL, \
			trace_thread, data + i);
	}
	i = -1;
	while (++i < THREADS)
		pthread_join(thread[i], NULL);
	SDL_UpdateWindowSurface(rtv->sdl.window);
}
