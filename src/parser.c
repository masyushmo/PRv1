/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasyush <mmasyush@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 18:30:13 by mmasyush          #+#    #+#             */
/*   Updated: 2019/09/17 14:28:30 by mmasyush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/rtv.h"

int		count_digits(char *line, int skip, int comp)
{
	int		i;
	int		digs;

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

int		get_int_value(char *line, int skip, int comp)
{
	int 	num;
	int		num_len;

	num = ft_atoi(line + skip);
	num_len = count_digits(line, skip, comp);
	if (num < 0)
		num_len++;
	if (skip + num_len == comp && num_len != 0)
		return (num);
	return (ft_error(BADNUM));
}

t_vector		get_vector_value(char *line, int skip)
{
	t_vector	nums;
	int			num_len;

	if(ft_strchr(line, '{'))
		nums.x = get_int_value(line, ft_strchr(line, '{') -
			line + 1, ft_strchr(line, ',') - line);
	else
		ft_error(BADNUM);
	if(ft_strchr(line, ','))
		nums.y = get_int_value(line, ft_strchr(line, ',') -
			line + 2, ft_strrchr(line, ',') - line);
	else
		ft_error(BADNUM);
	if(ft_strrchr(line, ','))
		nums.z = get_int_value(line, ft_strrchr(line, ',') -
			line + 2, ft_strchr(line, '}') - line);
	else
		ft_error(BADNUM);
	if (ft_strchr(line, '}') - line != (int)ft_strlen(line) - 1)
		ft_error(BADNUM);
	return (nums);
}

int		save_sphere(t_rtv *rtv, char *line)
{
	char	*l;

	l = ft_strtrim(line);
	if (ft_strncmp("radius = ", l, ft_strlen("radius = ")) == 0)
		rtv->map.obj[rtv->map.obj_num].sphere.rad =
			get_int_value(l, (int)ft_strlen("radius = "), (int)ft_strlen(l));
	if (ft_strncmp("center = ", l, ft_strlen("center = ")) == 0)
		rtv->map.obj[rtv->map.obj_num].sphere.o =
			get_vector_value(l, (int)ft_strlen("center = "));
	if (ft_strncmp("color = ", l, ft_strlen("color = ")) == 0)
		rtv->map.obj[rtv->map.obj_num].sphere.col =
			get_vector_value(l, (int)ft_strlen("color = "));
	// else
	// 	return (ft_error(BADFILE));
	return (1);
}

int		check_line(t_rtv *rtv, char *line, int *b)
{
	
	if (ft_strcmp("sphere {", line) == 0)
	{
		rtv->map.obj_num++;
		*b = 1;
		return (1);
	}
	else if (ft_strcmp("}", line) == 0)
	{
		*b = 0;
			printf("%d\n", *b);
		return (1);
	}
	else if (*b == 1 && save_sphere(rtv, line))
		return (1);
	return (0);
}

int		read_scene(t_rtv *rtv, char *filename)
{
	int		fd;
	int		bracket;
    char	*line;

	if ((fd = open(filename, O_RDONLY)) == -1)
		return (ft_error(BADFILE));
	rtv->map.obj_num = -1;
	bracket = 0;
	while (get_next_line(fd, &line) == 1)
	{
		if (!check_line(rtv, line, &bracket))
			return (0);
		free(line);
	}
	// printf("r:%d\n", rtv->map.obj[0].sphere.rad);
	// printf("x:%d\n", rtv->map.obj[0].sphere.o.x);
	// printf("y:%d\n", rtv->map.obj[0].sphere.o.y);
	// printf("z:%d\n", rtv->map.obj[0].sphere.o.z);
	// printf("R;%d\n", rtv->map.obj[0].sphere.col.x);
	// printf("G;%d\n", rtv->map.obj[0].sphere.col.y);
	// printf("B;%d\n\n", rtv->map.obj[0].sphere.col.z);
	
	// printf("r:%d\n", rtv->map.obj[1].sphere.rad);
	// printf("x:%d\n", rtv->map.obj[1].sphere.o.x);
	// printf("y:%d\n", rtv->map.obj[1].sphere.o.y);
	// printf("z:%d\n", rtv->map.obj[1].sphere.o.z);
	// printf("R;%d\n", rtv->map.obj[1].sphere.col.x);
	// printf("G;%d\n", rtv->map.obj[1].sphere.col.y);
	// printf("B;%d\n", rtv->map.obj[1].sphere.col.z);
	return (1);
}
