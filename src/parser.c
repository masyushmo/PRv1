/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasyush <mmasyush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 18:30:13 by mmasyush          #+#    #+#             */
/*   Updated: 2019/10/24 13:41:26 by mmasyush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv.h"

void check_color(t_vector color)
{
	if ((color[0] < 0 || color[0] > 255) || (color[1] < 0 || color[1] > 255)
		|| (color[2] < 0 || color[2] > 255))
		ft_error(BADCOL);
}

int			check_obj(t_map *map, char *line)
{
	static int obj_b = 0;
	static int light_b = 0;

	if (ft_strcmp("sphere {", line) == 0)
	{
		map->olist[map->onum] = SPHERE;
		obj_b = 1;
		return (1);
	}
	else if (ft_strcmp("plane {", line) == 0)
	{
		map->olist[map->onum] = PLANE;
		obj_b = 1;
		return (1);
	}
	else if (ft_strcmp("cylinder {", line) == 0)
	{
		map->olist[map->onum] = CYLINDER;
		obj_b = 1;
		return (1);
	}
	else if (ft_strcmp("cone {", line) == 0)
	{
		map->olist[map->onum] = CONE;
		obj_b = 1;
		return (1);
	}
	else if (ft_strcmp("light {", line) == 0)
	{
		light_b = 1;
		map->lnum++;
		return (1);
	}
	else if (ft_strcmp("}", line) == 0)
	{
		if (obj_b)
			obj_b = 0;
		if (light_b)
			light_b = 0;
		map->onum++;
		return (1);
	}
	else if (obj_b == 1 && map->olist[map->onum] == SPHERE && save_sphere(map, line) && map->onum < OBJ_MAX)
		return (1);
	else if (obj_b == 1 && map->olist[map->onum] == CYLINDER && save_cyl(map, line) && map->onum < OBJ_MAX)
		return (1);
	else if (obj_b == 1 && map->olist[map->onum] == PLANE && save_plane(map, line) && map->onum < OBJ_MAX)
		return (1);
	else if (obj_b == 1 && map->olist[map->onum] == CONE && save_cone(map, line) && map->onum < OBJ_MAX)
		return (1);
	else if (light_b == 1 && save_light(map, line) && map->onum < OBJ_MAX)
		return (1);
	return (0);
}

int			read_scene(t_map	*map, char	*filename)
{
	int			fd;
	char		*line;

	if ((fd = open(filename, O_RDONLY)) == -1)
		return (ft_error(BADFILE));
	if (!ft_brackets(filename))
		return (ft_error(BADFILE));
	map->onum = 0;
	map->lnum = 0;
	while (get_next_line(fd, &line) == 1)
	{
		if (!check_obj(map, line))
			return (0);
		free(line);
	}
	prepare_all(map);
	return (1);
}
