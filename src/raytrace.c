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

double      compute_ligh(t_rtv *rtv, t_vector P, t_vector normal)
{
    int i = -1;
    double inte = 0.0;
    double hz;
    t_vector light_d;

    while (++i <= rtv->map.lnum)
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
            hz = vect_dot(normal, light_d);
            
            if (hz > 0)
                inte += (rtv->map.light[i].i * hz / \
						(vect_len(light_d) * vect_len(normal)));
        }
    }
    return (inte);
}

t_inter     intersect_ray(t_vector camera, t_vector d, int n, t_rtv *rtv)
{
    t_inter temp;
    t_vector c = rtv->map.obj[n].sphere.o;
    double r = rtv->map.obj[n].sphere.rad;
    t_vector oc;
    oc[0] = camera[0] - c[0];
     oc[1] = camera[1] - c[1];
      oc[2] = camera[2] - c[2];
    
    double k1 = ((d[0] * d[0]) + (d[1] * d[1]) + (d[2] * d[2]));
    double k2 = 2 * ((oc[0] * d[0]) + (oc[1] * d[1]) + (oc[2] * d[2]));
    double k3 = ((oc[0] * oc[0]) + (oc[1] * oc[1]) + (oc[2] * oc[2])) - r * r;

    double dis = k2 * k2 - 4 * k1 * k3;
    if (dis < 0)
        return ((t_inter){T_MAX, T_MAX});
    temp[0] = (-k2 + sqrt(dis)) / (2 * k1);
    temp[1] = (-k2 - sqrt(dis)) / (2 * k1);
    return (temp);
}

t_vector    trace_ray(t_vector camera, t_vector d, t_rtv *rtv)
{
    t_inter    inter;
    double min_dist = T_MAX + 1;
    int closest_obj = -1;
    int n = -1;
        
    while(++n <= rtv->map.onum)
    {
        inter = intersect_ray(camera, d, n, rtv);
        if ((inter[0] > T_MIN && inter[0] < T_MAX) && (inter[0] < min_dist))
        {
            min_dist = inter[0];
            closest_obj = n;
        }
        if ((inter[1] > T_MIN && inter[1] < T_MAX) && (inter[1] < min_dist))
        {
            min_dist = inter[1];
            closest_obj = n;
        }
    }
    if (closest_obj == -1)
        return(BACKROUND);
    else
    {
        t_vector p = camera + vect_mult(d, min_dist);
	    t_vector normal = p - rtv->map.obj[closest_obj].sphere.o;
	    normal = vect_div(normal, vect_len(normal));
        return (vect_mult(rtv->map.obj[closest_obj].sphere.col,  compute_ligh(rtv, p, normal)));
    }
}

int     rgb_color(t_vector color)
{
    color[0] = CLAMP(color[0], 0, 255);
	color[1] = CLAMP(color[1], 0, 255);
	color[2] = CLAMP(color[2], 0, 255);
    return(((int)color[0] << 16) + ((int)color[1] << 8) + (int)color[2]);
} 

void	keyses(t_rtv *rtv)
{
	SDL_Event	event;

	if (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT || EXIT)
			rtv->quit = 1;
	}
}

void            trace_loop(t_rtv *rtv)
{
    int			x;
	int			y;
	t_vector	d;
	t_vector     color;
    t_vector    camera = {0, 0, 0};

	y = -WIN_H / 2 - 1;
	while (++y < WIN_H / 2)
	{
		x = -WIN_W / 2 - 1;
		while (++x < WIN_W / 2)
		{
			d = canvas_to_view(x, y);
            color = trace_ray(camera, d, rtv);
			put_pixel(x + WIN_W / 2, y + WIN_H / 2, rgb_color(color), rtv->sdl.surface);
		}
	}
	SDL_UpdateWindowSurface(rtv->sdl.window);
}


int			loop(t_rtv *rtv)
{
    rtv->quit = 0;
    trace_loop(rtv);
	while (rtv->quit == 0)
	{
        keyses(rtv);
	}
	return (0);
}
