/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasyush <mmasyush@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 15:49:01 by mmasyush          #+#    #+#             */
/*   Updated: 2019/09/04 15:49:01 by mmasyush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/rtv.h"

t_vector    trace_ray(t_vector camera, t_vector d, int t_min, int t_max)
{
    int min_dist = T_MAX;
    int closest_obj = -1;
    int n = -1;
    while(++n < obj_num)
    {

    }

}

int         read_scene(t_rtv *rtv, char *filename)
{
    int     fd;
    char    *line;

    if ((fd = open(filename, O_RDONLY)) == -1)
        return (error("BAD file"));
    
}

t_vector    canvas_to_view(int x, int y)
{
    double  v_h;
    double  v_w;

    v_w = (tan(FOW_RAD) * 2 * D);
    v_h = v_w * WIN_H / WIN_W;
    return ((t_vector){x * v_w / WIN_W, y * v_h / WIN_H, D});
}

int    main(int argc, char **argv)
{
    t_rtv   rtv;

    if (argc == 2)
    {
        if(!read_scene(&rtv, argv[1]))
            return (1);
        if(!init_sdl(&rtv.sdl))
            return (1);
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
                color = trace_ray(camera, d, T_MIN, T_MAX);

            }
        }
        SDL_UpdateWindowSurface(rtv.sdl.window);
    }
    else
        return (usage());
}
