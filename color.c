/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 20:45:10 by jkong             #+#    #+#             */
/*   Updated: 2022/04/28 16:47:51 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static unsigned char	*_t(int *color)
{
	const int	test = 0x0BADF00D;
	const int	endian = ((unsigned char *)&test)[0] != 0x0D;
	int			index;

	index = 0;
	if (!endian)
		index = (sizeof(*color) - 1) - index;
	return (&((unsigned char *)color)[index]);
}

static unsigned char	*_r(int *color)
{
	const int	test = 0x0BADF00D;
	const int	endian = ((unsigned char *)&test)[0] != 0x0D;
	int			index;

	index = 1;
	if (!endian)
		index = (sizeof(*color) - 1) - index;
	return (&((unsigned char *)color)[index]);
}

static unsigned char	*_g(int *color)
{
	const int	test = 0x0BADF00D;
	const int	endian = ((unsigned char *)&test)[0] != 0x0D;
	int			index;

	index = 2;
	if (!endian)
		index = (sizeof(*color) - 1) - index;
	return (&((unsigned char *)color)[index]);
}

static unsigned char	*_b(int *color)
{
	const int	test = 0x0BADF00D;
	const int	endian = ((unsigned char *)&test)[0] != 0x0D;
	int			index;

	index = 3;
	if (!endian)
		index = (sizeof(*color) - 1) - index;
	return (&((unsigned char *)color)[index]);
}

int	get_color(t_color *range, double rate)
{
	const double	inverse_rate = 1.0 - rate;
	int				result;

	*_t(&result) = inverse_rate * *_t(&range->begin) + rate **_t(&range->end);
	*_r(&result) = inverse_rate * *_r(&range->begin) + rate **_r(&range->end);
	*_g(&result) = inverse_rate * *_g(&range->begin) + rate **_g(&range->end);
	*_b(&result) = inverse_rate * *_b(&range->begin) + rate **_b(&range->end);
	return (result);
}
