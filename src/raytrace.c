/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasyush <mmasyush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 18:27:37 by mmasyush          #+#    #+#             */
/*   Updated: 2019/10/29 16:00:43 by mmasyush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv.h"

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

t_raycheck	close_inter(t_vector start, t_vector dir, double min, t_rtv *rtv)
{
	t_roots		roots;
	t_raycheck	temp;
	int			n;

	temp.min_dist = T_MAX;
	temp.close_obj = -1;
	n = -1;
	while (++n < rtv->map.onum)
	{
		roots = get_roots(start, dir, n, rtv);
		if (roots[0] > min && roots[0] < temp.min_dist)
		{
			temp.min_dist = roots[0];
			temp.close_obj = n;
		}
		if (roots[1] > min && roots[1] < temp.min_dist)
		{
			temp.min_dist = roots[1];
			temp.close_obj = n;
		}
	}
	return (temp);
}

t_vector	trace_ray(t_rtv *rtv, t_calc *calc)
{
	calc->check = close_inter(rtv->map.camera.pos, calc->dir, T_MIN, rtv);
	if (calc->check.close_obj == -1)
		return (BACKROUND);
	else if (rtv->map.olist[calc->check.close_obj] == SPHERE)
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

void		trace_loop(t_rtv *rtv)
{
	int			x;
	int			y;
	t_calc		calc;
	t_vector	color;

	calc.camera = rtv->map.camera.pos;
	y = -WIN_H / 2 - 1;
	while (++y < WIN_H / 2)
	{
		x = -WIN_W / 2 - 1;
		while (++x < WIN_W / 2)
		{
			calc.dir = canvas_to_view(x, y);
			calc.dir = rotate_cam(calc.dir, &rtv->map.camera);
			color = trace_ray(rtv, &calc);
			set_pixel(x + WIN_W / 2, y + WIN_H / 2, \
				rgb_color(color), rtv->sdl.surface);
		}
	}
	SDL_UpdateWindowSurface(rtv->sdl.window);
}

int			loop(t_rtv *rtv)
{
	rtv->quit = 0;
	while (rtv->quit == 0)
	{
		keyses(rtv);
		trace_loop(rtv);
	}
	return (0);
}
