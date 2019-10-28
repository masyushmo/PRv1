/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasyush <mmasyush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 18:27:37 by mmasyush          #+#    #+#             */
/*   Updated: 2019/10/28 18:19:13 by mmasyush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv.h"

t_raycheck         close_inter(t_vector start, t_vector dir, double min, double max, t_rtv *rtv)
{
    t_inter    inter;
    t_raycheck temp;

    temp.min_dist = T_MAX;
    temp.close_obj = -1;
    int n = -1;
        
    while(++n < rtv->map.onum - rtv->map.lnum)
    {
        if (rtv->map.olist[n] == SPHERE)
            inter = inter_sphere(start, dir, n, rtv);
        else if (rtv->map.olist[n] == CONE)
            inter = inter_cone(start, dir, n, rtv);
        else if (rtv->map.olist[n] == CYLINDER)
            inter = inter_cyl(start, dir, n, rtv);
        else if (rtv->map.olist[n] == PLANE)
            inter = inter_plane(start, dir, n, rtv);
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
    calc->check = close_inter(rtv->map.camera.pos, calc->dir, T_MIN, T_MAX, rtv);
    if (calc->check.close_obj == -1)
        return(BACKROUND);
    else if (rtv->map.olist[calc->check.close_obj] == SPHERE)
        return (sphere_norm(rtv, calc));
    else if (rtv->map.olist[calc->check.close_obj] == CONE)
        return (cone_norm(rtv, calc));
    else if (rtv->map.olist[calc->check.close_obj] == CYLINDER)
        return (cyl_norm(rtv, calc));
    else if (rtv->map.olist[calc->check.close_obj] == PLANE)
        return (plane_norm(rtv, calc));
    else 
        return(BACKROUND);
}

int     rgb_color(t_vector color)
{
    color[0] = CLAMP(color[0], 0, 255);
	color[1] = CLAMP(color[1], 0, 255);
	color[2] = CLAMP(color[2], 0, 255);
    return(((int)color[0] << 16) + ((int)color[1] << 8) + (int)color[2]);
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
			calc.dir = rotate_cam(calc.dir, &rtv->map.camera);
            color = trace_ray(rtv, &calc);
			set_pixel(x + WIN_W / 2, y + WIN_H / 2, rgb_color(color), rtv->sdl.surface);
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
