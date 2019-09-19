/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasyush <mmasyush@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 18:27:37 by mmasyush          #+#    #+#             */
/*   Updated: 2019/09/16 18:27:37 by mmasyush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv.h"

t_inter     intersect_ray(t_vector camera, t_vector d, int n, t_rtv *rtv)
{
    t_inter temp;
    t_vector c = rtv->map.obj[n].sphere.o;
    int r = rtv->map.obj[n].sphere.rad;
    t_vector oc;
    oc.x = camera.x - c.x;
     oc.y = camera.y - c.y;
      oc.z = camera.z - c.z;
    
    float k1 = ((d.x * d.x) + (d.y * d.y) + (d.z * d.z));
    float k2 = 2 * ((oc.x * d.x) + (oc.y * d.y) + (oc.z * d.z));
    float k3 = ((oc.x * oc.x) + (oc.y * oc.y) + (oc.z * oc.z)) - r * r;

    float dis = k2 * k2 - 4 * k1 * k3;
    if (dis < 0)
        return ((t_inter){T_MAX, T_MAX});
    temp.t1 = (-k2 + sqrt(dis)) / (2 * k1);
    temp.t2 = (-k2 - sqrt(dis)) / (2 * k1);
    return (temp);
}

t_vector    trace_ray(t_vector camera, t_vector d, t_rtv *rtv)
{
    t_inter    inter;
    int min_dist = T_MAX;
    int closest_obj = -1;
    int n = -1;
    while(++n < rtv->map.obj_num)
    {
        inter = intersect_ray(camera, d, n, rtv);
        if ((inter.t1 > T_MIN && inter.t1 < T_MAX) && (inter.t1 < min_dist))
        {
            min_dist = inter.t1;
            closest_obj = n;
        }
        if ((inter.t2 > T_MIN && inter.t1 < T_MAX) && (inter.t2 < min_dist))
        {
            min_dist = inter.t2;
            closest_obj = n;
        }
    }
    if (closest_obj == -1)
        return ((t_vector){255, 0, 0});
    return ((t_vector){rtv->map.obj[n].sphere.col.x, rtv->map.obj[n].sphere.col.y, rtv->map.obj[n].sphere.col.z});

}

t_vector	trim_color(t_vector color)
{
	color.x = CLAMP(color.x, 0, 255);
	color.y = CLAMP(color.y, 0, 255);
	color.z = CLAMP(color.z, 0, 255);
	return (color);
}

int     make_rgb(t_vector color)
{
    return(((int)color.x << 16) + ((int)color.y << 8) + (int)color.z);
} 

void            trace_loop(t_rtv *rtv)
{
    int			x;
	int			y;
	t_vector	d;
	t_vector	color;
    t_vector camera = {0, 0, 0};

	y = -WIN_H / 2 - 1;
	while (++y < WIN_H / 2)
	{
		x = -WIN_W / 2 - 1;
		while (++x < WIN_W / 2)
		{
			d = canvas_to_view(x, y);
            color = trace_ray(camera, d, rtv);
            color = trim_color(color);
			put_pixel(x + WIN_W / 2, y + WIN_H / 2, make_rgb(color), rtv->sdl.surface);
		}
	}
	SDL_UpdateWindowSurface(rtv->sdl.window);
}

int			loop(t_rtv *rtv)
{
	trace_loop(rtv);
	while (1)
	{
		trace_loop(rtv);
	}
	return (0);
}
