/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reg_fromto.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasyush <mmasyush@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 12:42:02 by mmasyush          #+#    #+#             */
/*   Updated: 2019/09/19 12:42:03 by mmasyush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char    *ft_reg_fromto(const char *src, int from, int to)
{
    int     from_i;
    int     to_i;
    char    *dst;

    from_i = ft_strchr(src, from) - src + 1;
    to_i = ft_strrchr(src, to) - src + 1;
    dst = (char*)ft_memalloc(sizeof(char) * (to_i - from_i));
    ft_strlcat(dst, src + from_i, to_i - from_i);
    return (dst);
}
