/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_digits.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasyush <mmasyush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 17:29:21 by mmasyush          #+#    #+#             */
/*   Updated: 2019/10/28 20:06:07 by mmasyush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv.h"

int	ft_count_digits(char *line, int skip, int comp)
{
	int			i;
	int			digs;

	i = skip;
	digs = 0;
	while (i < comp)
	{
		if (ft_isdigit(line[i]))
			digs++;
		i++;
	}
	return (digs);
}
