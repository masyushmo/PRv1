/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasyush <mmasyush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 18:30:13 by mmasyush          #+#    #+#             */
/*   Updated: 2019/11/13 18:00:30 by mmasyush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv.h"

void	check_color(t_vector color)
{
	if ((color[0] < 0 || color[0] > 255) || (color[1] < 0 || color[1] > 255)
		|| (color[2] < 0 || color[2] > 255))
		ft_error(BADCOL);
}

int		search_obj(t_map *map, char *line)
{
	if (ft_strcmp("sphere {", line) == 0)
		map->olist[map->onum] = SPHERE;
	else if (ft_strcmp("plane {", line) == 0)
		map->olist[map->onum] = PLANE;
	else if (ft_strcmp("cylinder {", line) == 0)
		map->olist[map->onum] = CYLINDER;
	else if (ft_strcmp("cone {", line) == 0)
		map->olist[map->onum] = CONE;
	else
		return (0);
	return (1);
}

int		save_obj(t_map *map, char *line, int *close)
{
	if (ft_strcmp("}", line) == 0)
	{
		map->onum++;
		*close = 0;
	}
	else if (map->olist[map->onum] == SPHERE)
		save_sphere(map, line);
	else if (map->olist[map->onum] == CYLINDER)
		save_cyl(map, line);
	else if (map->olist[map->onum] == PLANE)
		save_plane(map, line);
	else if (map->olist[map->onum] == CONE)
		save_cone(map, line);
	else
		return (0);
	return (1);
}

int		search_all(t_map *map, char *line)
{
	static int obj_b = 0;
	static int cam = 0;
	static int light_b = 0;

	if (ft_strcmp("camera {", line) == 0)
		cam++;
	else if (ft_strcmp("light {", line) == 0)
		light_b = 1;
	else if (search_obj(map, line))
		obj_b = 1;
	else if (cam == 1)
		save_camera(map, line);
	else if (obj_b && map->onum < OBJ_MAX)
		save_obj(map, line, &obj_b);
	else if (light_b && map->lnum < LIGHT_MAX)
		save_light(map, line, &light_b);
	else
		return (0);
	return (1);
}

int		read_scene(t_map *map, char *filename)
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
		if (!search_all(map, line))
			return (0);
		free(line);
	}
	prepare_all(map);
	return (1);
}
