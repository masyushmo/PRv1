/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geters.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasyush <mmasyush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 15:06:55 by mmasyush          #+#    #+#             */
/*   Updated: 2019/10/30 16:00:25 by mmasyush         ###   ########.fr       */
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

double		get_double(char *line, int skip, int comp)
{
	int			i1;
	int			i2;
	int			num_len;

	i1 = ft_atoi(line + skip);
	num_len = ft_count_digits(line, skip, comp) + 1;
	if (ft_strchr(line + skip, '.'))
		i2 = ft_atoi(line + (ft_strchr(line + skip, '.') - line + 1));
	else
	{
		i2 = 0;
		num_len = ft_count_digits(line, skip, comp);
	}
	if (i1 < 0 || !ft_strncmp("-0.", line + skip, ft_strlen("-0.")))
		num_len++;
	if (skip + num_len == comp && num_len != 0)
	{
		if (!ft_strncmp("-0.", line + skip, ft_strlen("-0.")))
			return (((double)i1 + i2 / (ft_expon(10, ft_num_size(i2)))) * -1);
		return ((double)i1 + i2 / (ft_expon(10, ft_num_size(i2))));
	}
	return (ft_error(BADNUM));
}

t_vector	get_vect(char *line)
{
	t_vector	nums;

	if (ft_strchr(line, '{'))
		nums[0] = get_double(line, ft_strchr(line, '{') -
			line + 1, ft_strchr(line, ',') - line);
	else
		ft_error(BADNUM);
	if (ft_strchr(line, ','))
		nums[1] = get_double(line, ft_strchr(line, ',') -
			line + 2, ft_strrchr(line, ',') - line);
	else
		ft_error(BADNUM);
	if (ft_strrchr(line, ','))
		nums[2] = get_double(line, ft_strrchr(line, ',') -
			line + 2, ft_strchr(line, '}') - line);
	else
		ft_error(BADNUM);
	if (ft_strchr(line, '}') - line != (int)ft_strlen(line) - 1)
		ft_error(BADNUM);
	return (nums);
}
