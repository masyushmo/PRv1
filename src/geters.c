/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geters.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasyush <mmasyush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 15:06:55 by mmasyush          #+#    #+#             */
/*   Updated: 2019/10/28 18:25:01 by mmasyush         ###   ########.fr       */
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
