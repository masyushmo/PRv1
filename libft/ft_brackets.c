/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_brackets.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasyush <mmasyush@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 15:23:16 by mmasyush          #+#    #+#             */
/*   Updated: 2019/09/19 15:23:18 by mmasyush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	match(char a, char b)
{
	return ((a == '[' && b == ']') || (a == '{' && b == '}') \
				|| (a == '(' && b == ')'));
}

static int	check(char *str, int *o, int *cl, int *pos)
{
	int         i;
	static int  stack[BUFF_SIZE];
    
	i = 0;
	while (str[i])
	{
		if (str[i] == '(' || str[i] == '{' || str[i] == '[')
        {
            *o += 1;
			stack[++(*pos)] = str[i];
        }
		if (str[i] == ')' || str[i] == '}' || str[i] == ']')
        {
            *cl += 1;
			if (!match(stack[(*pos)--], str[i]))
				return (0);
        }
		i += 1;
	}
	return (1);
}

int         ft_brackets(char *filename)
{
	char	*line;
    int     count_o;
    int     count_cl;
	int     pos;
	int		fd;

    count_cl = 0;
    count_o = 0;
	pos = 0;
	if ((fd = open(filename, O_RDONLY)) == -1)
		return (0);
    while (get_next_line(fd, &line) == 1)
	{
		if (!check(line, &count_o, &count_cl, &pos))
		    return (0);
		free(line);
	}
    if (count_cl == count_o)
    	return (1);
	return (0);
}