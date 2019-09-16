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

# include "../includes/rtv.h"

t_vector    canvas_to_view(int x, int y)
{
    double  v_h;
    double  v_w;

    v_w = (tan(FOW_RAD) * 2 * D);
    v_h = v_w * WIN_H / WIN_W;
    return ((t_vector){x * v_w / WIN_W, y * v_h / WIN_H, D});
}
