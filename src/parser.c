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

int		get_int_value(char *line, int skip)
{
	int num;
	int num_len;
	int i;

	i = skip;
	num_len = 0;
	while (ft_isdigit(line[i++]))
		num_len++;
	if (skip + num_len != (int)ft_strlen(line))
		return (ft_error("\033[0;31mBAD numbers"));
	num = ft_atoi(line + skip);
	if (num > 0)
		return (num);
	return (ft_error("\033[0;31mBAD numbers"));
}

int		save_sphere(t_rtv *rtv, char *line)
{
	char	*l;

	l = ft_strtrim(line);
	if (ft_strncmp("radius = ", l, ft_strlen("radius = ")) == 0)
		rtv->map.obj[rtv->map.obj_num].sphere.rad =
			get_int_value(l, (int)ft_strlen("radius = "));
	return (1);
}

int		check_line(t_rtv *rtv, char *line, int *b)
{
	if (ft_strcmp("sphere {", line) == 0)
	{
		*b = 1;
		return (1);
	}
	else if (ft_strcmp("}", line) == 0)
	{
		*b = 0;
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
		return (ft_error("BAD file"));
	rtv->map.obj_num = 0;
	bracket = 0;
	while (get_next_line(fd, &line) == 1)
	{
		// printf("%s\n", line);
		if (!check_line(rtv, line, &bracket))
			return (0);
		free(line);
	}
	return (1);
}
