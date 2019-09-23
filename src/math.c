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
