/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_v2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasyush <mmasyush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 18:13:47 by mmasyush          #+#    #+#             */
/*   Updated: 2019/11/13 16:55:30 by mmasyush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv.h"

int			rgb_color(t_vector color)
{
	color[0] = CLAMP(color[0], 0, 255);
	color[1] = CLAMP(color[1], 0, 255);
	color[2] = CLAMP(color[2], 0, 255);
	return (((int)color[0] << 16) + ((int)color[1] << 8) + (int)color[2]);
}

void		dir_angls(t_camera *camera)
{
	camera->cosx = cos(camera->dir[0] / 180 * M_PI);
	camera->cosy = cos(camera->dir[1] / 180 * M_PI);
	camera->sinx = sin(camera->dir[0] / 180 * M_PI);
	camera->siny = sin(camera->dir[1] / 180 * M_PI);
}

t_vector	rotate_cam(t_camera *cam, t_vector d)
{
	double xx;
	double yy;
	double zz;

	xx = d[0];
	yy = d[1];
	zz = d[2];
	d[0] = xx * cam->cosy - zz * cam->siny;
	d[2] = zz * cam->cosy + xx * cam->siny;
	zz = d[2];
	d[1] = yy * cam->cosx - zz * cam->sinx;
	d[2] = zz * cam->cosx + yy * cam->sinx;
	return (d);
}
