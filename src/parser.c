/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasyush <mmasyush@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 18:30:13 by mmasyush          #+#    #+#             */
/*   Updated: 2019/09/19 17:24:46 by mmasyush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv.h"

int			get_int(char *line, int skip, int comp)
{
	int			num;
	int			num_len;

	num = ft_atoi(line + skip);
	num_len = ft_count_digits(line, skip, comp);
	if (num < 0)
		num_len++;
	if (skip + num_len == comp && num_len != 0)
		return (num);
	return (ft_error(BADNUM));
}

double			get_double(char *line, int skip, int comp)
{
	int			i1;
	int			i2;
	int			num_len;

	i1 = ft_atoi(line + skip);
	num_len = ft_count_digits(line, skip, comp) + 1;
	if (ft_strchr(line, '.'))
		i2 = ft_atoi(line + (ft_strchr(line, '.') - line + 1));
	else
	{
		i2 = 0;
		num_len = ft_count_digits(line, skip, comp);
	}
	if (i1 < 0)
		num_len++;
	if (skip + num_len == comp && num_len != 0)
		return ((double)i1 + i2 / (ft_expon(10, ft_num_size(i2))));
	return (ft_error(BADNUM));
}

t_vector	get_vect(char *line)
{
	t_vector	nums;

	if (ft_strchr(line, '{'))
		nums[0] = get_int(line, ft_strchr(line, '{') -
			line + 1, ft_strchr(line, ',') - line);
	else
		ft_error(BADNUM);
	if (ft_strchr(line, ','))
		nums[1] = get_int(line, ft_strchr(line, ',') -
			line + 2, ft_strrchr(line, ',') - line);
	else
		ft_error(BADNUM);
	if (ft_strrchr(line, ','))
		nums[2] = get_int(line, ft_strrchr(line, ',') -
			line + 2, ft_strchr(line, '}') - line);
	else
		ft_error(BADNUM);
	if (ft_strchr(line, '}') - line != (int)ft_strlen(line) - 1)
		ft_error(BADNUM);
	return (nums);
}

int			save_sphere(t_map *map, char *line)
{
	char		*l;

	l = ft_strtrim(line);
	if (ft_strncmp("specular = ", l, ft_strlen("specular = ")) == 0)
		map->obj[map->onum].sphere.spec = get_int(l, \
			(int)ft_strlen("specular = "), (int)ft_strlen(l));
	if (ft_strncmp("radius = ", l, ft_strlen("radius = ")) == 0)
		map->obj[map->onum].sphere.rad = get_double(l, \
			(int)ft_strlen("radius = "), (int)ft_strlen(l));
	if (ft_strncmp("center = ", l, ft_strlen("center = ")) == 0)
		map->obj[map->onum].sphere.o = get_vect(l);
	if (ft_strncmp("color = ", l, ft_strlen("color = ")) == 0)
		map->obj[map->onum].sphere.col = get_vect(l);
	return (1);
}

int			save_light(t_map *map, char *line)
{
	char		*l;

	l = ft_strtrim(line);
	if (ft_strcmp("type = ambient", l) == 0)
		map->light[map->lnum].type = AMBIENT;
	else if(ft_strcmp("type = directional", l) == 0)
		map->light[map->lnum].type = DIRECT;
	else if (ft_strcmp("type = point", l) == 0)
		map->light[map->lnum].type = POINT;
	if (ft_strncmp("intensity = ", l, ft_strlen("intensity = ")) == 0)
		map->light[map->lnum].i = get_double(l, \
			(int)ft_strlen("intensity = "), (int)ft_strlen(l));
	if ((ft_strncmp("direction = ", l, ft_strlen("direction = ")) == 0) ||
		(ft_strncmp("position = ", l, ft_strlen("position = ")) == 0))
		map->light[map->lnum].vect = get_vect(l);
	return (1);
}

int			check_obj(t_map *map, char *line)
{
	static int obj_b = 0;
	static int light_b = 0;

	if (ft_strcmp("sphere {", line) == 0)
	{
		map->onum++;
		map->olist[map->onum] = SPHERE;
		obj_b = 1;
		return (1);
	}
	else if (ft_strcmp("light {", line) == 0)
	{
		map->lnum++;
		light_b = 1;
		return (1);
	}
	else if (ft_strcmp("}", line) == 0)
	{
		if (obj_b)
			obj_b = 0;
		if (light_b)
			light_b = 0;
		return (1);
	}
	else if (obj_b == 1 && map->olist[map->onum] == SPHERE && save_sphere(map, line) && map->onum < OBJ_MAX)
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
	map->onum = -1;
	map->lnum = -1;
	while (get_next_line(fd, &line) == 1)
	{
		if (!check_obj(map, line))
			return (0);
		free(line);
	}
	return (1);
}
