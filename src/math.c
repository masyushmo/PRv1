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
    return ((t_vector){x * VW / WIN_W, y * VH / WIN_H, D});
}
