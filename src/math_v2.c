/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_v2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasyush <mmasyush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 18:13:47 by mmasyush          #+#    #+#             */
/*   Updated: 2019/10/28 18:13:54 by mmasyush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv.h"

void    dir_angls(t_camera *camera)
{ 
    camera->cosx = cos(camera->dir[0] / 180 * M_PI);
    camera->cosy = cos(camera->dir[1] / 180 * M_PI);
    camera->sinx = sin(camera->dir[0] / 180 * M_PI);
    camera->siny = sin(camera->dir[1] / 180 * M_PI);
}

t_vector	rotate_cam(t_vector d, t_camera *cam)
{
    double new_x;
    double new_y;
    double new_z;

    new_x = d[0] * cam->cosy + d[2] * cam->siny;
    new_z = -d[0] * cam->siny + d[2] * cam->cosy;
    d[0] = new_x;
    d[2] = new_z;
    new_y = d[1] * cam->cosx + d[2] * cam->sinx;
    new_z = -d[1] * cam->sinx + d[2] * cam->cosx;
    d[1] = new_y;
    d[2] = new_z;
    return (d);
}