/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_map_read.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 15:42:06 by jkong             #+#    #+#             */
/*   Updated: 2022/04/21 22:32:01 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#include <fcntl.h>
#include "get_next_line.h"

static t_str_list	*_next_str_node(int fd)
{
	t_str_list	*result;
	char		*str;

	str = get_next_line(fd);
	if (!str)
		return (NULL);
	result = malloc_safe(sizeof(t_str_list));
	result->str = str;
	result->next = NULL;
	return (result);
}

static void	_insert_str_node(t_str_list **head, t_str_list *node)
{
	t_str_list	*tail;

	if (*head)
	{
		tail = *head;
		while (tail->next)
			tail = tail->next;
		tail->next = node;
	}
	else
		*head = node;
}

static t_map_loader	*_read_all_text(const char *path)
{
	t_map_loader	*result;
	int				fd;
	t_str_list		*node;
	int				do_first;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	result = malloc_safe(sizeof(*result));
	result->count = 0;
	result->head = NULL;
	node = NULL;
	do_first = 1;
	while (do_first || node)
	{
		node = _next_str_node(fd);
		_insert_str_node(&result->head, node);
		result->count++;
		do_first = 0;
	}
	close(fd);
	return (result);
}

static void	_free_loader(t_map_loader *loader)
{
	t_str_list	*detach;
	t_str_list	*destruct;

	if (loader)
	{
		detach = loader->head;
		loader->head = NULL;
		while (detach)
		{
			destruct = detach;
			detach = detach->next;
			free(destruct);
		}
	}
	free(loader);
}

int	fdf_read_map(t_fdf_map *map, char *path)
{
	int				result;
	t_map_loader	*loader;

	result = 0;
	map->path = path;
	loader = _read_all_text(map->path);
	if (loader && loader->head)
	{
		map->dim.x = ft_split_count(loader->head->str, " ");
		map->dim.y = loader->count;
		map->arr = calloc_safe(map->dim.x * map->dim.y, sizeof(*map->arr));
		result = fdf_load_map(map, loader);
	}
	_free_loader(loader);
	return (result);
}
