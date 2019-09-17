/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasyush <mmasyush@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 13:07:08 by mmasyush          #+#    #+#             */
/*   Updated: 2019/09/16 13:07:08 by mmasyush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/rtv.h"

int			ft_error(char *message)
{
	ft_putstr(message);
	ft_putchar('\n');
	return (0);
}

int			usage(void)
{
	ft_putstr("usage: ./rtv {map}\n");
	return (0);
}