/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasyush <mmasyush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 18:28:31 by mmasyush          #+#    #+#             */
/*   Updated: 2019/10/28 19:39:24 by mmasyush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv.h"

t_vector	canvas_to_view(int x, int y)
{
	return ((t_vector){(double)x * VW /
		WIN_W, -(double)y * VH / WIN_H, (double)D});
}

t_vector	vect_mult(t_vector a, double k)
{
	return (t_vector){a[0] * k, a[1] * k, a[2] * k};
}

t_vector	vect_div(t_vector a, double k)
{
	return (t_vector){a[0] / k, a[1] / k, a[2] / k};
}

double		vect_dot(t_vector a, t_vector b)
{
	return (a[0] * b[0] + a[1] * b[1] + a[2] * b[2]);
}

double		vect_len(t_vector a)
{
	return (sqrt(vect_dot(a, a)));
}
