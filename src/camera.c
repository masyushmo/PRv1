/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasyush <mmasyush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 19:03:26 by mmasyush          #+#    #+#             */
/*   Updated: 2019/10/29 16:01:34 by mmasyush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv.h"

int			save_camera(t_map *map, char *line)
{
	char		*l;

	l = ft_strtrim(line);
	if (ft_strcmp("}", line) == 0)
	{
		free(l);
		return (1);
	}
	else if (ft_strncmp("position = ", l, ft_strlen("position = ")) == 0)
		map->camera.pos = get_vect(l);
	else if (ft_strncmp("direction = ", l, ft_strlen("direction = ")) == 0)
		map->camera.dir = get_vect(l);
	else
		ft_error(BADLINE);
	free(l);
	return (1);
}
