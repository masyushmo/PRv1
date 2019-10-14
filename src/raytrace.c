/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasyush <mmasyush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 18:27:37 by mmasyush          #+#    #+#             */
/*   Updated: 2019/10/14 18:20:23 by mmasyush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv.h"

double      compute_ligh(t_rtv *rtv, t_vector P, t_vector normal, int spec, t_vector d)
{
    int i = -1;
    double inte = 0.0;
    double hz;
    double zz;
    t_raycheck rtmp;
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
        
            rtmp = close_inter(P, light_d, 0.001, T_MAX, rtv);
            if (rtmp.close_obj != -1)
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

t_inter     inter_sphere(t_vector camera, t_vector d, int n, t_rtv *rtv)
{
    t_inter temp;
    t_vector c = rtv->map.obj[n].sphere.o;
    double r = rtv->map.obj[n].sphere.rad;
    t_vector oc;
    oc = camera - c;
    
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

t_inter     inter_cyl(t_vector camera, t_vector d, int n, t_rtv *rtv)
{
    t_inter temp;
    t_vector c = rtv->map.obj[n].cylinder.o;
    double r = rtv->map.obj[n].cylinder.rad;
    t_vector oc;
    oc = camera - c;
    
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

t_raycheck         close_inter(t_vector start, t_vector dir, double min, double max, t_rtv *rtv)
{
    t_inter    inter;
    t_raycheck temp;

    temp.min_dist = T_MAX + 1;
    temp.close_obj = -1;
    int n = -1;
        
    while(++n <= rtv->map.onum)
    {
        inter = inter_sphere(start, dir, n, rtv);
        if ((inter[0] > min && inter[0] < max) && (inter[0] < temp.min_dist))
        {
            temp.min_dist = inter[0];
            temp.close_obj = n;
        }
        if ((inter[1] > min && inter[1] < max) && (inter[1] < temp.min_dist))
        {
            temp.min_dist = inter[1];
            temp.close_obj = n;
        }
    }
    return (temp);
}

t_vector    trace_ray(t_rtv *rtv, t_calc *calc)
{
    calc->check = close_inter(calc->camera, calc->dir, T_MIN, T_MAX, rtv);
    if (calc->check.close_obj == -1)
        return(BACKROUND);
    else if (calc->check.close_obj == CYLINDER)
    {
        double m;

        m = vect_dot(calc->dir, rtv->map.obj[calc->check.close_obj].cylinder.dir) * calc->check.min_dist + vect_dot(calc->camera - rtv->map.obj[calc->check.close_obj].cylinder.o, rtv->map.obj[calc->check.close_obj].cylinder.dir);
        t_vector p = calc->camera + vect_mult(calc->dir, calc->check.min_dist);
	    t_vector normal = p - rtv->map.obj[calc->check.close_obj].cylinder.o - vect_mult(rtv->map.obj[calc->check.close_obj].cylinder.dir, m);
	    normal = vect_div(normal, vect_len(normal));
        return (vect_mult(rtv->map.obj[calc->check.close_obj].sphere.col,  compute_ligh(rtv, p, normal, rtv->map.obj[calc->check.close_obj].sphere.spec, -calc->dir)));
    }
    else
    {
        t_vector p = calc->camera + vect_mult(calc->dir, calc->check.min_dist);
	    t_vector normal = p - rtv->map.obj[calc->check.close_obj].sphere.o;
	    normal = vect_div(normal, vect_len(normal));
        return (vect_mult(rtv->map.obj[calc->check.close_obj].sphere.col,  compute_ligh(rtv, p, normal, rtv->map.obj[calc->check.close_obj].sphere.spec, -calc->dir)));
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
    int chosen = 1;
	SDL_Event	event;
    const Uint8 *state;

	state = SDL_GetKeyboardState(NULL);
	if (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT || EXIT)
			rtv->quit = 1;
        if (event.type == SDL_KEYDOWN)
        {
            printf("%d\n\n", rtv->map.obj[chosen].sphere.spec);
            if (event.key.keysym.sym == 1073741920)
                rtv->map.obj[chosen].sphere.o[1] += 0.1;
            if (event.key.keysym.sym == 1073741914)
                rtv->map.obj[chosen].sphere.o[1] -= 0.1;
            if (event.key.keysym.sym == 1073741916)
                rtv->map.obj[chosen].sphere.o[0] -= 0.1;
            if (event.key.keysym.sym == 1073741918)
                rtv->map.obj[chosen].sphere.o[0] += 0.1;
            if (event.key.keysym.sym == 1073741917 && state[SDL_SCANCODE_TAB])
                rtv->map.obj[chosen].sphere.o[2] -= 0.1;
            else if (event.key.keysym.sym == 1073741917)
                rtv->map.obj[chosen].sphere.o[2] += 0.1;
            if (event.key.keysym.sym == 1073741910)
                rtv->map.obj[chosen].sphere.spec -= 20;
            if (event.key.keysym.sym == 1073741911)
                rtv->map.obj[chosen].sphere.spec += 20;
            if (rtv->map.obj[chosen].sphere.spec > 1000)
                rtv->map.obj[chosen].sphere.spec = 1000;
            if (rtv->map.obj[chosen].sphere.spec < 0)
                rtv->map.obj[chosen].sphere.spec = 0;
           
            //     rtv->map.obj[0].sphere.o[1] += 1;
            //     rtv->map.obj[0].sphere.o[2] += 1;
            // }

        }
	}
}

void            trace_loop(t_rtv *rtv)
{
    int			x;
	int			y;
    t_calc      calc;
	t_vector    color;
    calc.camera = (t_vector){0, 0, 0};

	y = -WIN_H / 2 - 1;
	while (++y < WIN_H / 2)
	{
		x = -WIN_W / 2 - 1;
		while (++x < WIN_W / 2)
		{
			calc.dir = canvas_to_view(x, y);
            color = trace_ray(rtv, &calc);
			put_pixel(x + WIN_W / 2, y + WIN_H / 2, rgb_color(color), rtv->sdl.surface);
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
