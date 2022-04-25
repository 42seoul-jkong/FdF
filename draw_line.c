/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 16:05:39 by jkong             #+#    #+#             */
/*   Updated: 2022/04/25 21:25:12 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#include <unistd.h>
#include "mlx.h"

static size_t	_abs_diff(size_t a, size_t b)
{
	if (a < b)
		return (b - a);
	else
		return (a - b);
}

void	draw_line(t_fdf *unit, t_point2 a, t_point2 b, int color)
{
	const t_point2	dst = {_abs_diff(a.x, b.x), _abs_diff(a.y, b.y)};
	const t_point2	sgn = {a.x < b.x, a.y < b.y};
	ssize_t			err;
	t_point2		t;

	err = dst.x - dst.y;
	put_pixel(unit, a.x, a.y, color);
	while (a.x != b.x || a.y != b.y)
	{
		t.x = (ssize_t)(2 * err - dst.x) < 0;
		t.y = (ssize_t)(2 * err + dst.y) > 0;
		if (t.y)
		{
			err -= dst.y;
			a.x += ((int)sgn.x << 1) - 1;
		}
		if (t.x)
		{
			err += dst.x;
			a.y += ((int)sgn.y << 1) - 1;
		}
		put_pixel(unit, a.x, a.y, color);
	}
}
