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

# include "../includes/rtv.h"

t_vector    trace_ray(t_vector camera, t_vector d, t_rtv *rtv)
{
    int min_dist = T_MAX;
    int closest_obj = -1;
    int n = -1;
    while(++n < )
    {

    }

}

void            trace_loop(t_rtv *rtv)
{
    t_vector camera = {0, 0, 0};
    int x = -WIN_W / 2;
    int y = -WIN_H / 2;
    while (y <= WIN_H / 2)
    {
        while (x <= WIN_W / 2)
        {
            t_vector    d;
            t_vector    color;
            d = canvas_to_view(x, y);
            color = trace_ray(camera, d, rtv);
        }
    }
    SDL_UpdateWindowSurface(rtv->sdl.window);
}