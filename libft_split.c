/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 13:15:54 by jkong             #+#    #+#             */
/*   Updated: 2022/04/18 15:55:06 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_calloc(size_t count, size_t size);

static int	_contains(char c, const char *set)
{
	if (!set)
		return (0);
	while (*set && *set != c)
		set++;
	return (*set == c);
}

size_t	ft_split_count(const char *s, const char *set)
{
	size_t	count;
	int		on_elem;

	if (!s)
		return (-1);
	count = 0;
	on_elem = 0;
	while (*s)
	{
		if (_contains(*s++, set))
			on_elem = 0;
		else if (!on_elem)
		{
			count++;
			on_elem = 1;
		}
	}
	return (count);
}

static int	_split_elem(char **ptr, const char *s, const char *set)
{
	size_t	i;
	char	*elem;

	while (*s)
	{
		if (_contains(*s, set))
			s++;
		else
		{
			i = 0;
			while (s[i] && !_contains(s[i], set))
				i++;
			elem = ft_calloc(i + 1, sizeof(char));
			*ptr++ = elem;
			if (elem == NULL)
				return (0);
			while (*s && !_contains(*s, set))
				*elem++ = *s++;
			*elem = '\0';
		}
	}
	*ptr = NULL;
	return (1);
}

char	**ft_split_free(char **ptr)
{
	char	**tab;

	if (ptr)
	{
		tab = ptr;
		while (*tab)
		{
			free(*tab);
			*tab++ = NULL;
		}
		free(ptr);
		ptr = NULL;
	}
	return (ptr);
}

char	**ft_split(const char *s, const char *set)
{
	char	**result;

	if (!s)
		return (NULL);
	result = ft_calloc(ft_split_count(s, set) + 1, sizeof(char *));
	if (result == NULL || !_split_elem(result, s, set))
		return (ft_split_free(result));
	return (result);
}
