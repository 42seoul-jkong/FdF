/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 15:42:06 by jkong             #+#    #+#             */
/*   Updated: 2022/05/03 19:44:28 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_fdf_point	*get_pos(t_fdf_map *map, long x, long y)
{
	return (&map->arr[x + y * map->dim.x]);
}

static int	_default_color(int value)
{
	if (value < 5)
		return (0xFFFFFF);
	else if (value < 10)
		return (0xCCCC00);
	else
		return (0x880088);
}

static int	_load_line(t_fdf_map *map, long y, char **line)
{
	char		**info;
	t_fdf_point	*point;
	long		x;

	x = 0;
	while (line[x] && x < map->dim.x)
	{
		info = ft_split(line[x], ",");
		if (!info)
			exit(EXIT_FAILURE);
		point = get_pos(map, x, y);
		if (info[0])
		{
			point->value = ft_strtoi(info[0]);
			if (info[1])
				point->color = ft_strtoi(info[1]);
			else
				point->color = _default_color(point->value);
		}
		ft_split_free(info);
		x++;
	}
	return (x == map->dim.x);
}

int	fdf_load_map(t_fdf_map *map, t_map_loader *loader)
{
	int				result;
	t_str_list		*node;
	char			**line;
	long			y;

	node = loader->head;
	y = 0;
	while (node)
	{
		line = ft_split(node->str, " ");
		if (!line)
			exit(EXIT_FAILURE);
		result = _load_line(map, y, line);
		ft_split_free(line);
		if (!result)
			return (0);
		node = node->next;
		y++;
	}
	return (1);
}

t_rect	bound_fdf(t_fdf_map *map)
{
	t_rect		rect;
	t_fdf_point	*pos;
	long		i;

	i = 0;
	while (i < map->dim.x * map->dim.y)
	{
		pos = get_pos(map, i % map->dim.x, i / map->dim.x);
		if (i == 0 || rect.left > pos->coord.x)
			rect.left = pos->coord.x;
		if (i == 0 || rect.right < pos->coord.x)
			rect.right = pos->coord.x;
		if (i == 0 || rect.top > pos->coord.y)
			rect.top = pos->coord.y;
		if (i == 0 || rect.bottom < pos->coord.y)
			rect.bottom = pos->coord.y;
		i++;
	}
	return (rect);
}
