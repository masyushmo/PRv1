/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sublen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasyush <mmasyush@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 13:19:01 by mmasyush          #+#    #+#             */
/*   Updated: 2019/09/19 13:19:01 by mmasyush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int    ft_sublen(const char *src, int from, int to)
{
    char    *temp;
    int     len;
    
    temp = ft_reg_fromto(src, from, to);
    len = ft_strlen(temp);
    return (len);
}
