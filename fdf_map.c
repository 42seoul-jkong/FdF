/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 15:42:06 by jkong             #+#    #+#             */
/*   Updated: 2022/04/21 22:03:47 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_fdf_point	*get_pos(t_fdf_map *map, size_t x, size_t y)
{
	return (&map->arr[x + y * map->dim.x]);
}

static int	_load_line(t_fdf_map *map, size_t y, char **line)
{
	char		**info;
	t_fdf_point	*point;
	size_t		x;

	x = 0;
	while (line[x])
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
				point->color = 0xFFFFFF;
		}
		ft_split_free(info);
		x++;
	}
	return (1);
}

int	fdf_load_map(t_fdf_map *map, t_map_loader *loader)
{
	int				result;
	t_str_list		*node;
	char			**line;
	size_t			y;

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
