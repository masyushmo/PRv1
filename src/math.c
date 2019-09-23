/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasyush <mmasyush@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 18:28:31 by mmasyush          #+#    #+#             */
/*   Updated: 2019/09/16 18:28:31 by mmasyush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv.h"

t_vector    canvas_to_view(int x, int y)
{
    double v_w;
    double v_h;

    v_w = VW;
    v_h = VH;
    return ((t_vector){(double)x * v_w / WIN_W, -(double)y * v_h / WIN_H, (double)D});
}

t_vector	vect_mult(t_vector a, double k)
{
	return (t_vector){a[0] * k, a[1] * k, a[2] * k};
}

t_vector	vect_div(t_vector a, double k)
{
	return (t_vector){a[0] / k, a[1] / k, a[2] / k};
}

double      vect_dot(t_vector a, t_vector b)
{
	return (a[0] * b[0] + a[1] * b[1] + a[2] * b[2]);
}

double      vect_len(t_vector a)
{
	return (ft_sqrt(vect_dot(a, a)));
}
