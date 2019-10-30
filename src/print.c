/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasyush <mmasyush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 13:07:08 by mmasyush          #+#    #+#             */
/*   Updated: 2019/10/30 18:56:39 by mmasyush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv.h"

int			ft_error(char *message)
{
	ft_putstr(message);
	ft_putchar('\n');
	exit(1);
}

int			usage(void)
{
	ft_putstr("usage: ./rtv scene/{map}\n");
	return (0);
}
